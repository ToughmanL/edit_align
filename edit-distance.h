
#include <vector>


template<class T>
void ReverseVector(std::vector<T> *vec) {
  int sz = vec->size();
  for (int i = 0; i < sz/2; i++)
    std::swap( (*vec)[i], (*vec)[sz-1-i]);
}

class EditAlign {
  public:
    template<class T>
    int LevenshteinAlignment(const std::vector<T> &a,
                           const std::vector<T> &b,
                           T eps_symbol,
                           std::vector<std::pair<T, T> > *output) {
      output->clear();
      // This is very memory-inefficiently implemented using a vector of vectors.
      int M = a.size(), N = b.size();
      int m, n;
      std::vector<std::vector<int> > e(M+1);
      for (m = 0; m <=M; m++) e[m].resize(N+1);
      for (n = 0; n <= N; n++)
        e[0][n]  = n;
      for (m = 1; m <= M; m++) {
        e[m][0] = e[m-1][0] + 1;
        for (n = 1; n <= N; n++) {
          int sub_or_ok = e[m-1][n-1] + (a[m-1] == b[n-1] ? 0 : 1);
          int del = e[m-1][n] + 1;  // assumes a == ref, b == hyp.
          int ins = e[m][n-1] + 1;
          e[m][n] = std::min(sub_or_ok, std::min(del, ins));
        }
      }
      // get time-reversed output first: trace back.
      m = M;
      n = N;
      while (m != 0 || n != 0) {
        int last_m, last_n;
        if (m == 0) {
          last_m = m;
          last_n = n-1;
        } else if (n == 0) {
          last_m = m-1;
          last_n = n;
        } else {
          int sub_or_ok = e[m-1][n-1] + (a[m-1] == b[n-1] ? 0 : 1);
          int del = e[m-1][n] + 1;  // assumes a == ref, b == hyp.
          int ins = e[m][n-1] + 1;
          // choose sub_or_ok if all else equal.
          if (sub_or_ok <= std::min(del, ins)) {
            last_m = m-1;
            last_n = n-1;
          } else {
            if (del <= ins) {  // choose del over ins if equal.
              last_m = m-1;
              last_n = n;
            } else {
              last_m = m;
              last_n = n-1;
            }
          }
        }
        T a_sym, b_sym;
        a_sym = (last_m == m ? eps_symbol : a[last_m]);
        b_sym = (last_n == n ? eps_symbol : b[last_n]);
        output->push_back(std::make_pair(a_sym, b_sym));
        m = last_m;
        n = last_n;
      }
      ReverseVector(output);
      return e[M][N];
    }
};
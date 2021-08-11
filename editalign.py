
# Return variable type
def getType(variate):
    arr = {"str":"str","list":"list"}
    vartype=None
    if isinstance(variate,list):
        vartype = "list"
    elif isinstance(variate,str):
        vartype = "str"
    if not (vartype in arr):
        return "unknow type"
    return arr[vartype]

def levenshtein(in_a, in_b):
  a = []
  b = []
  eps_sumbol = "_"
  output = []
  if getType(in_a) == "str":
    a = list(in_a)
    b = list(in_b)
  M = len(a)
  N = len(b)
  e = [[0 for col in range(N+1)] for row in range(M+1)]
  for n in range(N + 1):
    e[0][n] = n
  for m in range(1, M + 1):
    e[m][0] = e[m - 1][0] + 1
    for n in range(1, N + 1):
      if a[m-1] == b[n-1]:
        sub_or_ok = 0
      else:
        sub_or_ok = 1
      sub_or_ok = e[m-1][n-1] + sub_or_ok
      dele = e[m-1][n] + 1
      inse = e[m][n-1] + 1
      e[m][n] = min(sub_or_ok, min(dele, inse))
  m = M
  n = N
  while n != 0 or m != 0:
    last_m = 0
    last_n = 0
    if m == 0:
      last_m = m
      last_n = n - 1
    elif n == 0:
      last_m = m -1
      last_n = n
    else:
      if a[m-1] == b [n-1]:
        sub_or_ok = 0
      else:
        sub_or_ok = 1
      sub_or_ok = e[m-1][n-1] + sub_or_ok
      dele = e[m-1][n] + 1
      inse = e[m][n-1] + 1
      if sub_or_ok <= min(dele, inse):
        last_m = m - 1
        last_n = n - 1
      else:
        if dele <= inse:
          last_m = m - 1
          last_n = n
        else:
          last_m = m
          last_n = n - 1
    a_sym = eps_sumbol if (last_m == m) else a[last_m]
    b_sym = eps_sumbol if (last_n == n) else b[last_n]
    tmp_sym = []
    tmp_sym.append(a_sym)
    tmp_sym.append(b_sym)
    output.append(tmp_sym)
    m = last_m
    n = last_n
  r_output = output[::-1]
  return r_output

def main():
  in_a = "adfgn" # original str
  in_b = "asdfgh"   # new str
  output = levenshtein(in_a, in_b)
  print(output)

main()
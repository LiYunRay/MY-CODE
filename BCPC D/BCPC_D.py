import math
T=int(input())
for _ in range(T):
    n=int(input())
    A=[];
    if(n==2):
        A.append("1");
        A.append("2");
    else:
        d=math.isqrt(n-1)+1
        m=n//d
        A=list(range(1,d+1))
        for j in range(2,m+1):
            v=j*d
            if(v<=n):
                A.append(v)
        A.append(n)
        A=sorted(set(A))
    print(len(A))
    print(" ".join(map(str,A)))


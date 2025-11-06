a,b=map(int,input().split())
for i in range(a,b+1):
    temp=0
    now=i
    big=0
    total=0
    while(10**big<=i):
        big+=1
    
    while now>=10:
        temp+=(now%10)**big
        now=int(now/10)
        temp+=now**big
    if(temp==i):
        total+=1
        print(i)
    
if(total==0):
   print(f"[{a},{b}]内没有水仙花数")
        


s=input()
temp=1
arr=[]
n=int(input())
for i in range(0,len(s)-1):
    if(s[i]==s[i+1]):
        temp+=1
    elif(s[i]!=s[i+1]):
        if(temp>=3):
            arr.append(temp)
        temp=1
if(temp>=3):
    arr.append(temp)
    temp=1
arr.sort(reverse=True)
while arr[0]>=3 and n>0:
    arr[0]-=1;
    arr.sort(reverse=True)
    print(arr)
    n-=1
fin=0;

for item in arr:
    if item>=3:
       fin+=item**3
print(fin)
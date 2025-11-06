c = input().strip()
s, m, h, d, mo = c.split()
md = [31,28,31,30,31,30,31,31,30,31,30,31]

if s == "*":
    cs = 60
elif "," in s:
    sv = list(map(int, s.split(",")))
    cs = 0
    for v in sv:
        if 0 <= v <= 59:
            cs += 1
elif "-" in s:
    a, b = map(int, s.split("-"))
    cs = b - a + 1 if a <= b and 0 <= a and b <= 59 else 0
else:
    v = int(s)
    cs = 1 if 0 <= v <= 59 else 0

if m == "*":
    cm = 60
elif "," in m:
    mv = list(map(int, m.split(",")))
    cm = 0
    for v in mv:
        if 0 <= v <= 59:
            cm += 1
elif "-" in m:
    a, b = map(int, m.split("-"))
    cm = b - a + 1 if a <= b and 0 <= a and b <= 59 else 0
else:
    v = int(m)
    cm = 1 if 0 <= v <= 59 else 0

if h == "*":
    ch = 24
elif "," in h:
    hv = list(map(int, h.split(",")))
    ch = 0
    for v in hv:
        if 0 <= v <= 23:
            ch += 1
elif "-" in h:
    a, b = map(int, h.split("-"))
    ch = b - a + 1 if a <= b and 0 <= a and b <= 23 else 0
else:
    v = int(h)
    ch = 1 if 0 <= v <= 23 else 0

vm = []
if mo == "*":
    vm = list(range(1,13))
elif "," in mo:
    mov = list(map(int, mo.split(",")))
    for v in mov:
        if 1 <= v <= 12:
            vm.append(v)
elif "-" in mo:
    a, b = map(int, mo.split("-"))
    if a <= b and 1 <= a <= 12 and 1 <= b <= 12:
        vm = list(range(a, b+1))
else:
    v = int(mo)
    if 1 <= v <= 12:
        vm.append(v)

cdt = 0
for mn in vm:
    dm = md[mn - 1]
    if d == "*":
        cd = dm
    elif "," in d:
        dv = list(map(int, d.split(",")))
        cd = 0
        for v in dv:
            if 1 <= v <= dm:
                cd += 1
    elif "-" in d:
        a, b = map(int, d.split("-"))
        start = max(a, 1)
        end = min(b, dm)
        cd = end - start + 1 if start <= end else 0
    else:
        v = int(d)
        cd = 1 if 1 <= v <= dm else 0
    cdt += cd

t = cs * cm * ch * cdt
print(t)


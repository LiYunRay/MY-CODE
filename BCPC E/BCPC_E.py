a = input()
if a == 'sheify':
    k=10000000
    p = list(input().strip().split())
    counts = {}
    for item in p:
        if item in counts:
            counts[item] += 1
        else:
            counts[item] = 1
    for item in counts:
        k=min(k,counts[item])

    if "she" in p:
        print(" ".join(p))
    else:
        for item in p:
            if counts[item] == k:
                target = item
                break
        for i in range(0, len(p)):
            if p[i] == target:
                p[i] = "she"
                break
        print(" ".join(p))

elif a == 'desheify':
    p = list(input().strip().split())
    counts = {}
    k=1000000
    for item in p:
        if item!="she":
            if item in counts:
                counts[item] += 1
            else:
                counts[item] = 1
    for item in counts:
        k=min(k,counts[item])
    for item in counts:
        if counts[item]==k:
            target=item
            break
    she_count = counts.get("she", 0)
    if she_count >= 2:
        print(" ".join(p))
    else:
        if len(p) >= 2 and p[0] == "she" and counts.get(p[1], 0) == len(p) - 1:
            p[0] = p[1]
        else:
            for i in range(0, len(p)):
                if p[i] == "she":
                    p[i] = target
                    break
        print(" ".join(p))
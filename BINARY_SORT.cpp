sorted = false
while (sorted == false) :
    sorted = true
    for i = 0 to n - 2 :
        if a[i + 1] < a[i] :
            swap(a[i + 1], a[i])
            sorted = false
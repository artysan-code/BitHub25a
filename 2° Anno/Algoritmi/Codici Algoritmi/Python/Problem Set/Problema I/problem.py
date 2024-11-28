def strbalance(sequence):
    chiuse = 0
    aperte = 0
    for char in sequence:
        if char == ')':
            if aperte > 0:
                aperte -= 1
            else:
                chiuse += 1
        elif char == '(':
            aperte += 1
    if aperte == chiuse:
        return str(chiuse)
    else:
        return "+∞"

result = ["O(n)", "O(1)"]

test_var = []
test_var.append(["(()())", "0"])
test_var.append(["())(()", "1"])
test_var.append(["((()))", "0"])
test_var.append(["())()(", "1"])
test_var.append(["(()", "+∞"])
test_var.append(["())", "+∞"])
test_var.append(["(", "+∞"])
test_var.append([")", "+∞"])
test_var.append([")()())((", "2"])
test_var.append(["()())", "+∞"])
test_var.append([")()(", "1"])
test_var.append(["()()()", "0"])
test_var.append(["()())","+∞"])
test_var.append([")(","1"])
test_var.append(["())()(","1"])
test_var.append([")()","+∞"])
test_var.append([")()))()(((","3"])

for a in test_var:
    if(a[1] == strbalance(a[0])):
        print("Risultato: "," SUCCESS \n")
    else:
        print("Risultato aspettato: '",a[1],"' \nRisultato ottenuto: '", strbalance(a[0]),"' \nRisultato: "," FAIL ", "\n") 
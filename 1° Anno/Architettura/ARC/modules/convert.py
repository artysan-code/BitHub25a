def convert_base(num: str, from_base: int, to_base: int) -> None:
    base10_num = int(num, from_base)
    
    if to_base == 10:
        print(f"\n\nIl numero {num} convertito in base {to_base} è {base10_num}.\n")
        return
    
    digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    
    if base10_num == 0:
        return "0"

    result = ""
    
    while base10_num > 0:
        result = digits[base10_num % to_base] + result
        base10_num //= to_base
    
    print(f"\n\nIl numero {num} convertito in base {to_base} è {result}.\n")

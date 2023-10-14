from cs50 import get_int
import re


def get_card_type(num_str):
    # American Expressは34または37で始まり、15桁
    if re.match(r"^3[47][0-9]{13}$", num_str):
        return "AMEX"
    # MasterCardは51、52、53、54、55で始まり、16桁
    elif re.match(r"^5[12345][0-9]{14}$", num_str):
        return "MASTERCARD"
    # Visaは4始まり、13桁もしくは16桁
    elif re.match(r"^4([0-9]{12}|[0-9]{15})$", num_str):
        return "VISA"
    else:
        return "INVALID"


while True:
    q = get_int("Number: ")
    if re.match(r"^[0-9]{10,16}$", str(q)):
        break
    else:
        pass


card_type = get_card_type(str(q))

print(card_type)

def is_common(x: str, y: str, z: str) -> bool:
    x_length = len(x)
    y_length = len(y)
    z_length = len(z)
    i = found_in_x = found_in_y = 0

    while i < z_length:
        x_i = i

        for j in range(found_in_x, x_length):
            if x_i >= z_length:
                break
            if x[j] == z[x_i]:
                found_in_x += 1
                x_i += 1

        for j in range(found_in_y, y_length):
            if i >= z_length:
                break
            if y[j] == z[i]:
                found_in_y += 1
                i += 1
        i += 1

    return found_in_x == z_length == found_in_y


if __name__ == '__main__':
    x_test = "abcdefgyxykz"
    y_test = "defghijk"
    z_test = "defgk"
    print(is_common(x_test, y_test, z_test))

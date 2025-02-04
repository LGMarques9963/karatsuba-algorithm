import subprocess
import random
from tqdm import tqdm as tqdm

def call_c_program(c_program_path, arguments=[]):
    """Emulates calling a C program through the terminal and reading the response.

    Args:
        c_program_path: The path to the C program executable.
        arguments: A list of arguments to pass to the C program.

    Returns:
        The output of the C program as a string.
    """

    try:
        result = subprocess.run(
            [c_program_path] + arguments,
            capture_output=True,
            text=True
        )
    except subprocess.CalledProcessError as e:
        print(f"Error running C program: {e}")
        return None
    
    # Find the index of "Soma: " in the output
    # print(result)
    # index = result.stdout.find("Resultado: ")
    # if index != -1:
    #     # Extract the substring after "Soma: "
    #     return result.stdout[index + len("Resultado: "):].strip()
    # else:
    #     print("Could not find 'Resultado: ' in the output.")
    #     print(f"Output: {result.stdout}")
    #     return None

    return result.stdout.strip()

def generate_random_binary(lenght):
    """Generates a random binary string of a given length.

    Args:
        lenght: The length of the binary string to generate.

    Returns:
        A random binary string of the given length.
    """

    return "".join([str(random.randint(0, 1)) for _ in range(lenght)])

# Example usage:
c_program_path = "./refactor"
# a1 = "1010101010101010010101010111100101010101"
# a2 = "101010101001010101010111111010101010101010110010100101"
# arguments = [a1, a2]
# print(f"a1: {a1}")
# print(f"a2: {a2}")
# output = call_c_program(c_program_path, arguments)
# a3 = int(a1, 2) * int(a2, 2)
# expected = bin(a3)[2:]
# print(f"Expected: {expected}")
# print(f"Output: {output}")
# print(f"Output == Expected: {int(output,2) == int(expected,2)}")
# print(output)
number_bits = 128000


# Leia o arquivo zz.txt

try:
    # with open("zz.txt", "r") as f:
    #     lines = f.readlines()
    #     for line in tqdm(lines):
    #         if line.strip() == "":
    #             continue
    #         a1, a2 = line.strip().split(" ")
    #         arguments = [a1, a2] if int(a1, 2) > int(a2, 2) else [a2, a1]
    #         output = call_c_program(c_program_path, arguments)
    #         a3 = int(arguments[0], 2) * int(arguments[1], 2)
    #         expected = bin(a3)[2:]
    #         expected = expected[1:] if expected[0] == "b" else expected
    #         if int(output,2) != int(expected,2):
    #             print(f"a1: {a1}")
    #             print(f"a2: {a2}")
    #             print(f"Expected: {expected}")
    #             print(f"Expected_10: {int(expected,2)}")
    #             print(f"Output: {output}")
    #             print(f"Output_10: {int(output,2)}")
                # raise Exception("Output != Expected")
    for _ in tqdm(range(10)):
        a1 = generate_random_binary(random.randint(1,number_bits))
        a2 = generate_random_binary(random.randint(1,number_bits))
        # a1 = "10"
        # a2 = "11"
        arguments = [a1, a2] if int(a1, 2) > int(a2, 2) else [a2, a1]
        # print(f"a1: {arguments[0]}, {int(arguments[0], 2)}")
        # print(f"a2: {arguments[1]}, {int(arguments[1], 2)}")
        try:
            output = call_c_program(c_program_path, arguments)
            a3 = int(arguments[0], 2) * int(arguments[1], 2)
            expected = bin(a3)[2:]
        # print(f"Expected: {expected}, {a3}")
        # print(f"Output: {output}")
            expected = expected[1:] if expected[0] == "b" else expected
            if int(output,2) != int(expected,2):
                print(f"a1: {a1}")
                print(f"a2: {a2}")
                print(f"Expected: {expected}")
                print(f"Expected_10: {int(expected,2)}")
                print(f"Output: {output}")
                print(f"Output_10: {int(output,2)}")
                raise Exception("Output != Expected")
        except Exception as e:
            print(f"Error: {e}")
            print(f"a1: {a1}")
            print(f"a2: {a2}")
            print(f"Expected: {expected}")
            print(f"Output: {output}")
            raise Exception("Test failed.")

except Exception as e:
    print(f"Error: {e}")
    print("Test failed.")
else:
    print("Test passed.")
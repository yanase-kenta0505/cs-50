import csv
import sys


def main():
    # コマンドライン引数の確認
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # データの読み込み
    with open(sys.argv[1], newline="") as csvfile:
        reader = csv.reader(csvfile)
        # ヘッダー行のSTRシーケンスの名前を配列で取得
        # ["AGATC", "AATG", "TATC"]
        all_sequences = next(reader)[1:]

        people = {}
        for row in reader:
            name = row[0]
            
            sequences = []
            for item in row[1:]:
                sequences.append(int(item))

            # 以下のようなオブジェクトを生成する
            # {"AGATC":2, "AATG": 8, "TATC": 3}
            sequences_dict = {}
            for i in range(len(all_sequences)):
                sequences_dict[all_sequences[i]] = sequences[i]

            people[name] = sequences_dict

    with open(sys.argv[2]) as file:
        s = file.read()

    # STRカウント
    actual = {}
    for seq in all_sequences:
        actual[seq] = str(max_repeats(s, seq))

    # マッチング
    for name, sequences in people.items():
        if all(actual[seq] == str(sequences[seq]) for seq in all_sequences):
            print(name)
            return
    print("No match")


def max_repeats(s, sub):
    """Return the maximum number of times that sub repeats in s."""
    repeats = [0] * (len(s) + 1)

    for i in range(len(s) - len(sub), -1, -1):
        if s[i : i + len(sub)] == sub:
            repeats[i] = 1 + repeats[i + len(sub)]
        else:
            repeats[i] = 0

    return max(repeats)


if __name__ == "__main__":
    main()

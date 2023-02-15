def read_fasta_file(filename):
    sequences = []
    with open(filename, "r") as f:
        temp = ""
        for line in f:
            if line.startswith(">"):
                if temp:
                    sequences.append(temp)
                    temp = ""
            else:
                temp += line.strip()
        sequences.append(temp)
    return sequences
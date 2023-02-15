import global_alignment as ga
import utils as util

seqs = util.read_fasta_file("Input.fasta")
seq1 = seqs[0]
seq2 = seqs[1]
print(seq1)
print(seq2)

gap_open = -4
gap_extend = -1
match = 1
mismatch = -1
align1, align2, score = ga.needleman_wunsch_affine(seq1, seq2, gap_open, gap_extend, match, mismatch)

print("Sequence 1: " + seq1)
print("Sequence 2: " + seq2)
print("Alignment 1: " + align1)
print("Alignment 2: " + align2)
print("Alignment Score: " + str(score))
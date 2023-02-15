import numpy as np

def needleman_wunsch_affine(seq1, seq2, gap_open, gap_extend, match_score, mismatch_score):
    # Initialize the matrices
    n = len(seq1)
    m = len(seq2)
    M = np.zeros((n+1, m+1))
    Ix = np.zeros((n+1, m+1))
    Iy = np.zeros((n+1, m+1))

    # Initialize the gap penalties
    gap_open_penalty = gap_open
    gap_extend_penalty = gap_extend

    # Fill in the first row and column
    for i in range(1, n+1):
        M[i][0] = -gap_open_penalty - (i-1) * gap_extend_penalty
        Ix[i][0] = -gap_open_penalty - (i-1) * gap_extend_penalty
        Iy[i][0] = float("-inf")
    for j in range(1, m+1):
        M[0][j] = -gap_open_penalty - (j-1) * gap_extend_penalty
        Ix[0][j] = float("-inf")
        Iy[0][j] = -gap_open_penalty - (j-1) * gap_extend_penalty

    # Fill in the rest of the matrices
    for i in range(1, n+1):
        for j in range(1, m+1):
            # Match/mismatch score
            match = match_score if seq1[i-1] == seq2[j-1] else mismatch_score

            # Calculate the scores for each of the three matrices
            match_score = M[i-1][j-1] + match
            gap_x_score = Ix[i-1][j-1] + match
            gap_y_score = Iy[i-1][j-1] + match

            # Choose the best score for the current position
            M[i][j] = max(match_score, gap_x_score, gap_y_score)
            Ix[i][j] = max(M[i-1][j] - gap_open_penalty - gap_extend_penalty, Ix[i-1][j] - gap_extend_penalty)
            Iy[i][j] = max(M[i][j-1] - gap_open_penalty - gap_extend_penalty, Iy[i][j-1] - gap_extend_penalty)

    # Traceback to find the optimal alignment
    align1 = ""
    align2 = ""
    i, j = n, m
    while i > 0 or j > 0:
        if i > 0 and j > 0 and M[i][j] == M[i-1][j-1] + (match_score if seq1[i-1] == seq2[j-1] else mismatch_score):
            align1 = seq1[i-1] + align1
            align2 = seq2[j-1] + align2
            i -= 1
            j -= 1
        elif i > 0 and M[i][j] == Ix[i][j]:
            align1 = seq1[i-1] + align1
            align2 = "-" + align2
            i -= 1
        elif j > 0 and M[i][j] == Iy[i][j]:
            align1 = "-" + align1
            align2 = seq2[j-1] + align2
            j -= 1

    return align1, align2, M[n][m]

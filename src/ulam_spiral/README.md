

# Calculating what iteration to stop at based on the size of the grid:

Rule: i\*8 = total amount of elements in that iteration \
One row contains (i\*8-4)/4 + 2 elements \
So, total_rows = (i\*8-4)/4 + 2  \

rows - 2 = (i\*8-4)/4 \
4(rows-2) = i\*8-4 \
4(rows-2)+4 = i\*8 \
 i = (4(rows-2)+4)/8 \
i = (4rows-8+4)/8 \
i = (4rows-4)/8 \
i = (rows-1)/2 \
        
Example: rows = 154 \
i = (154-1)/2 = 76.5 \
ROUND UP (ceil) \
i = 77

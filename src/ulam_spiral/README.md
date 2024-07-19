
# ULAM'S SPIRAL

## Running
Make sure `CMakeLists.txt` contains `add_executable(main src/ulam_spiral/main.cpp)`

### Option 1 - Default Dimensions
Compile: `cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release`
Build: `./build/bin/main`

### Option 2 - Custom Dimensions
Add the size of rows and columns. Use even dimensions. You can run with odd dimensions, it will just round to an even number.

Compile: `cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release`
Build: `./build/bin/main <number>`

Example:  `./build/bin/main 200` will run with 200 rows and 200 columns

<hr>

## Code Explanations

<b>Calculating what iteration to stop at based on the size of the grid:</b>

<u>Note:</u> $i*8$ = total amount of elements in iteration $i$ \
One row contains $ (i*8-4)/4 + 2 $ elements \
So, $\text{total\_rows} = (i*8-4)/4 + 2$ elements

$\text{rows} - 2 = (i*8-4)/4$ \
$4(\text{rows}-2) = i*8-4 $\
$4(\text{rows}-2)+4 = i*8$ \
$i = (4(\text{rows}-2)+4)/8$ \
$i = (4\text{rows}-8+4)/8 $\
$i = (4\text{rows}-4)/8 $\
$i = (\text{rows}-1)/2$

# HTML Parser Project

## Project Description

This project is a C++ utility designed to parse and scale HTML configuration files. It reads an HTML file containing UI element properties (such as width, height, offsets, and font sizes) and applies mathematical transformations to these values based on predefined scaling coefficients.

### Purpose

The parser is useful for:
- Converting UI dimensions between different aspect ratios
- Scaling interface elements proportionally
- Automating responsive design transformations
- Batch processing HTML configuration files

### How It Works

The program:
1. Reads an input HTML file (`Tekst.html`)
2. Uses regular expressions to identify and extract numeric values for:
   - **Width and X-Offset** (multiplied by 1.5)
   - **Height and Y-Offset** (multiplied by 1.78, representing 16:9 aspect ratio)
   - **Font Size and Title Font Size** (multiplied by 2.35)
3. Recalculates the values using the respective coefficients
4. Outputs the modified HTML to a new file (`Tekst_out.html`)

## Installation & Setup

### Requirements
- C++ compiler (g++ or gcc)
- Linux/Unix environment (or compatible shell)

### Building the Project

Using the Makefile:
```bash
make
```

This will compile all `.cpp` files in the directory and create executables with the `Exec` suffix.

Or manually with g++:
```bash
g++ parser.cpp -o parserExec
```

## Usage

### Basic Execution

```bash
./parserExec
```

The program will:
1. Look for an input file named `Tekst.html` in the current directory
2. Process all matching XML/HTML tags
3. Generate an output file named `Tekst_out.html`

### Input File Format

The input HTML file (`Tekst.html`) should contain tags in the following format:

```xml
<itemWidth><int>100</itemWidth>
<itemHeight><int>200</itemHeight>
<xOffset><int>50</xOffset>
<yOffset><int>75</yOffset>
<fontSize><int>12</fontSize>
<titleFontSize><int>16</titleFontSize>
```

### Output

The program generates `Tekst_out.html` with scaled values:

```xml
<itemWidth><int>150</itemWidth>
<itemHeight><int>356</itemHeight>
<xOffset><int>75</xOffset>
<yOffset><int>133</yOffset>
<fontSize><int>28</fontSize>
<titleFontSize><int>37</titleFontSize>
```

## Scaling Coefficients

| Property | Coefficient | Purpose |
|----------|-------------|---------|
| itemWidth, xOffset | 1.5 | Width-based scaling |
| itemHeight, yOffset | 1.78 | Height-based scaling (16:9 ratio) |
| fontSize, titleFontSize | 2.35 | Font size scaling |

These coefficients can be modified in the source code for different scaling requirements.

## File Structure

```
.
├── parser.cpp          # Main program source code
├── Makefile            # Build configuration
├── Tekst.html          # Input HTML file
├── Tekst_out.html      # Generated output file
└── README.md           # This file
```

## Cleaning Up

To remove compiled executables:

```bash
make clean
```


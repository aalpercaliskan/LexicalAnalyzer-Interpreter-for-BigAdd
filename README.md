# The BigAdd Language

BigAdd language is a small programming language that has been designed in order to add and subtract big integers programmatically and display the result on the screen. The lexical analyzer and interpreter for the BigAdd language works from the command line with the command 'file extension file name' respectively.

![image](https://user-images.githubusercontent.com/112978786/194415661-6b3419d9-995c-49c3-a954-e12e95f6a081.png)


This command load the script file called myscript.ba and perform lexical analysis and interpreter on it. The results of the lexical analysis written into a file with the same name and ".lx" extension. (For the example above The file myscript.lx will be created) This file should contain a suitable representation of a token at each line. (Each token should be written on a separate line)

**Lines of Code:**

Point ('.') is the end of line character. Lines can contain keywords, brackets, variables and constants. Any number of spaces or comments can be used between these elements. A program line can be divided between multiple text lines.

A line of code is one of the following:

• A variable declaration.

• An assignment statement.

• An addition statement.

• A subtraction statement.

• An output statement.

• A loop statement.

**Comments**

Comments are written between curly braces { }

**Data Types**

The only data type for variables is the integer. Integer is a signed whole number that is represented as a decimal data type. An integer can be as big as 100 decimal digits.

Strings exist only as constants and are used in the out statements only.

**example:** 123113, -5 3.14159 is not a valid integer (it is a real number)

3.0 is not a valid integer (decimal point should not be displayed)

3. is not a valid integer (decimal point should not be displayed)

- 5 is not a valid integer (there should be no blank between the minus sign and the first digit.

--5 is not a valid integer (only one minus sign allowed)

+5 is not a valid integer (plus sign is not allowed), 0, -314159 are valid integer representations.

**Variables**

All variables should be declared as an integer. Variables must be declared before they are used. All variables are global (and static).

int \<variable\>.

Variable names are case sensitive and have a maximum length of 20 characters. Variable names start with a letter (alphabetical character) and continue with alphanumeric characters or an underscore character.

All variables are initialized with the value 0 at the time of creation.

**Assignment Statement**

move \<int\_value\> to \<variable\>.

**Addition statement**

add \<int\_value\> to \<variable\>.

Increments the variable by int value.

**Subtraction statement**

sub \<int\_value\> from \<variable\>.

**Output statement**

out \<out\_list\>.

**An integer value is either a variable or a constant**

\<int\_value\>→\<variable\>|\<int\_const\>

**An output list is a list of strings and integer values separated by commas**

\<out\_list\>→\<out\_list\>,\<list\_element\>|\<list\_element\>

\<list\_element\>→\<int\_value\>|\<string\>| newline

A string is any sequence of characters between two quotation marks.

**Loop**

loop \<int\_value\> times \<line\>

{OR}

loop \<int\_value\> times \<code\_block\>

A loop starts with the int\_value and at each iteration decrements the value of int\_value by one. If int\_value is a variable, the value of the variable can be accessed and modified during the loop. After the loop the variable takes the value 0. The last iteration of the loop operates with the value 1.

**Code Block**

A code block is a list of code lines between square brackets. A code block can be used in a loop, interchangeably with a single line of code. By using code blocks, loops may be nested within each other.

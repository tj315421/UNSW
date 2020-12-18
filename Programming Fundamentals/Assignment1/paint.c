// Assignment 1 20T3 COMP1511: CS Paint
// paint.c
//
// This program was written by Leon-Liao (z5306312)
// on 12/10/2020 - 22/10/2020
//
// Version 1.0.0 (2020-10-04): Assignment released.
//
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// The dimensions of the canvas (20 rows x 36 columns).
#define N_ROWS 20
#define N_COLS 36

// Shades (assuming your terminal has a black background).
#define BLACK 0
#define WHITE 4

// IF YOU NEED MORE #defines ADD THEM HERE
#define DRAW_LINE_COMMAND 1
#define RECTANGLE_COMMAND 2
#define COLOURED_COMMAND 3
#define COPY_COMMAND 4
#define MACRO_RECORD 5
#define MACRO_PLAYBACK 6 
#define SAVE_STATE 7
#define TEM_ARRAY_SIZE 100
#define MAX_GROUPS 10
#define MIN_GROUPS 0
#define TOTAL_COMMAND_DIGITS 5

// Provided helper functions:

// Display the canvas.
void display_canvas(int canvas[N_ROWS][N_COLS]);

// Clear the canvas by setting every pixel to be white.
void clear_canvas(int canvas[N_ROWS][N_COLS]);

// Stage1 && Stage2.
//
// Draw line & diagonas.
void draw_line(
    int canvas[N_ROWS][N_COLS], 
    int command_number, 
    int shade_index
);

// Draw rectangle.
void fill_rectangle(
    int canvas[N_ROWS][N_COLS], 
    int command_number, 
    int shade_index
);

// Change shade.
int change_shade(int command_number);

// Stage3.
//
// Copy and paste.
void copy_paste(int canvas[N_ROWS][N_COLS], int command_number);

// Stage4.
//
// Macro playback.
void macro_playback(
    int command_number, 
    int num_commands, 
    int saved_array[10][5], 
    int canvas[N_ROWS][N_COLS],
    int shade_index
);

// Draw line & diagonas1.
// Used in Stage4 - marco_playback.
void draw_line1(
    int canvas[N_ROWS][N_COLS], 
    int command_number, 
    int start_row, 
    int start_col, 
    int end_row, 
    int end_col, 
    int shade_index
);

// Draw rectangle1.
// Used in Stage4 - marco_playback.
void fill_rectangle1(
    int canvas[N_ROWS][N_COLS], 
    int command_number, 
    int start_row, 
    int start_col, 
    int end_row, 
    int end_col,
    int shade_index
);

// Stage5.
//
// Save state.
void save_state(int save_current[20][36], int canvas[N_ROWS][N_COLS]);

int main(void) {
    int canvas[N_ROWS][N_COLS];
    int command_number = 0;
    
    clear_canvas(canvas);
    // TODO: Add your code here!
     
    // Use scanf loop, and scan command_number.    
    int ret_val = scanf("%d ", &command_number);
    int shade_index = change_shade(command_number);
    
    // Stage 4.
    //    
    // Macro record.
    //
    // Set an array to record commands.
    // Max groups of commands is 10 (assignment requirement), 
    // and every command has 5 digits. e.g. 1 1 1 1 1
    int num_commands = 0;
    int saved_array[MAX_GROUPS][TOTAL_COMMAND_DIGITS];
    
    if (command_number == MACRO_RECORD) { 
        scanf("%d", &num_commands);
        
        // Record every 5 digits into 1 row of the saved_array.
        int i = 0;
        while (
            i < num_commands 
            && num_commands >= MIN_GROUPS 
            && num_commands <= MAX_GROUPS
            ) {
            int j = 0;
            while (j < TOTAL_COMMAND_DIGITS) {
                scanf(" %d", &saved_array[i][j]);
                j++;
            }
            i++;
        }
    }      
    
    // Use [0,4] interval, only let valid shade_index go in.
    // BLACK = 0.
    // WHITE = 4.     
    while (ret_val == 1 && shade_index >= BLACK && shade_index <= WHITE) {
        
        // Stage 5.
        // 
        // Save.
        //
        // Set an array to copy elements of the current canvas.
        // Display current saved array. 
        if (command_number == SAVE_STATE) {       
            int save_current[N_ROWS][N_COLS];
            save_state(save_current, canvas);

            while (ret_val == 1) {
                draw_line(canvas, command_number, shade_index);    
                fill_rectangle(canvas, command_number, shade_index);
                copy_paste(canvas, command_number);
                macro_playback(
                    command_number, 
                    num_commands, 
                    saved_array, 
                    canvas, 
                    shade_index
                );                 
                ret_val = scanf("%d ", &command_number); 
            }               
            display_canvas(save_current);
            printf("\n");
            
            // When enter other commands except SAVE_STATE = 7.       
        } else if (command_number != SAVE_STATE) {    
            draw_line(canvas, command_number, shade_index);    
            fill_rectangle(canvas, command_number, shade_index);
            copy_paste(canvas, command_number);
            macro_playback(
                command_number, 
                num_commands, 
                saved_array, 
                canvas, 
                shade_index
            ); 
                
            // When get COLOURED_COMMAND = 3, 
            // calculate NEW shade_index,
            // and go through while loop again 
            // with the NEW shade_index.
            ret_val = scanf("%d ", &command_number);          
            if (command_number == COLOURED_COMMAND) {
                shade_index = change_shade(command_number);
            } 
        }    
    }
    display_canvas(canvas);          
}

// ADD CODE FOR YOUR FUNCTIONS HERE

// Stage5.
//
// Save state.
//
// Copy all elements that are in the current canvas array,
// set them into the temporary save_current array.
void save_state(int save_current[N_ROWS][N_COLS], int canvas[N_ROWS][N_COLS]) { 
    int i = 0;
    while (i < N_ROWS) {
        int j = 0;
        while (j < N_COLS) {
            save_current[i][j] = canvas[i][j];
            j++;
        }
        i++;
    }
}

// Stage4.
//
// Macro playback.
//
// Shift the recorded commands.
// Execute each of the saved commands in order.
// The lines and rectangles should be created in the current colour.
void macro_playback(
    int command_number, 
    int num_commands, 
    int saved_array[MAX_GROUPS][TOTAL_COMMAND_DIGITS], 
    int canvas[N_ROWS][N_COLS],
    int shade_index
) {

    // Use the saved_array which has recorded sets of commands
    // during the macro_record stage,
    // then use row_offset and col_offset to adjust these commands.                
    if (command_number == MACRO_PLAYBACK) {
        int row_offset = 0, col_offset = 0;
        scanf("%d %d", &row_offset, &col_offset);
        
        int start_row, 
            start_col, 
            end_row, 
            end_col;
                    
        int i = 0;
        while (i < num_commands) {
            command_number = saved_array[i][TOTAL_COMMAND_DIGITS - 5];
            start_row = saved_array[i][TOTAL_COMMAND_DIGITS - 4] + row_offset;
            start_col = saved_array[i][TOTAL_COMMAND_DIGITS - 3] + col_offset;
            end_row = saved_array[i][TOTAL_COMMAND_DIGITS - 2] + row_offset;
            end_col = saved_array[i][TOTAL_COMMAND_DIGITS - 1] + col_offset;
            
            // Excute draw_line1 && fill_rectangle1 functions.
            draw_line1(
                canvas, 
                command_number, 
                start_row, 
                start_col, 
                end_row, 
                end_col, 
                shade_index
            );            
            fill_rectangle1(
                canvas, 
                command_number, 
                start_row, 
                start_col, 
                end_row, 
                end_col, 
                shade_index
            );
                                           
            i++;
        }
    }
}
// Stage3.
//
// Copy and paste.
//
// Copy a certain section of the canvas, 
// and paste it elsewhere on the canvas.
void copy_paste(int canvas[N_ROWS][N_COLS], int command_number) {
    
    if (command_number == COPY_COMMAND) {
        int start_row, 
            start_col, 
            end_row, 
            end_col, 
            target_row, 
            target_col;
        
        scanf(
            "%d %d %d %d %d %d", 
            &start_row, 
            &start_col, 
            &end_row, 
            &end_col, 
            &target_row, 
            &target_col
        );
          
        // Set sets of saved_values to store the values,
        // in order to avoid some values might be changed in some process.
        //        
        // Set a temporay array which is BIG enough.
        int saved_value1 = start_col;
        int saved_value2 = target_col;
        int saved_value3 = start_row;
        int saved_value4 = end_row;
        int saved_value5 = end_col;

        int tem_array[TEM_ARRAY_SIZE][TEM_ARRAY_SIZE];
        
        // Using counters i,j and loop.
        // Copy the changed values from canvas,
        // and put them into the temporay array.
        int i, j;        
        i = 0;
        start_row = saved_value3;
        while (start_row <= end_row) {            
            // From top left side.
            start_col = saved_value1;
            j = 0;
            while (start_col <= end_col) {                            
                tem_array[i][j] = canvas[start_row][start_col];
                j++;
                start_col++;
            }            
            // From top right side.
            end_col = saved_value5;
            while (end_col < start_col) {                
                tem_array[i][j] = canvas[start_row][end_col];                
                j++;
                end_col++;
            }                        
            i++;
            start_row++;
        }
        
        end_row = saved_value4;
        while (end_row < start_row) {            
            // From bot left side.
            start_col = saved_value1;
            j = 0;
            while (start_col <= end_col) {                
                tem_array[i][j] = canvas[end_row][start_col];                
                j++;
                start_col++;
            }            
            // From bot right side.
            end_col = saved_value5;
            while (end_col < start_col) {                
                tem_array[i][j] = canvas[end_row][end_col];                
                j++;
                end_col++;
            }                        
            i++;
            end_row++;
        }
        
        // Using counters i,j and loop.
        // Copy values from temporay array to target array
        // to achieve the overlap function.
        //
        // Using absolute value to avoid the repeat 
        // when start_row > end_row or end_row > start_row.
        int distance_row = abs(saved_value4 - saved_value3);
        i = 0;
        
        // If the target part is outside the canvas,
        // paste the parts that are inside the canvas.
        //
        // When target_row <= 0, 
        // paste the lower part that is inside the canvas.
        // When target_row > 35, 
        // paste the upper part that is inside the canvas.
        if (target_row <= 0) {            
            i = - target_row;
            target_row = 0;
        } else if (target_row > N_ROWS - 1) {
            i = 0;
            distance_row = N_ROWS - 1 - target_row;
        } 
        
        while (i <= distance_row) {        
            int distance_col = abs(saved_value5 - saved_value1);           
            target_col = saved_value2;
            j = 0;
            
            // When target_col <= 0, 
            // paste the right part that is inside the canvas.
            // When target_col > 35, 
            // paste the left part that is inside the canvas.
            if (target_col + distance_col > N_COLS - 1) {
                j = 0;
                distance_col = N_COLS - 1 - target_col;
            } else if (target_col <= 0) {
                j = - target_col;
                target_col = 0;
            }
            
            while (j <= distance_col) {
                canvas[target_row][target_col] = tem_array[i][j];                
                j++;
                target_col++;
            }            
            i++;
            target_row++;
        }        
    }
}

// Stage2.
//
// Change shade.
//
// Given one additional integer: the new shade
// that you will draw in all future commands, 
// until the shade is changed again.
// Start with the shade BLACK.
int change_shade(int command_number) {
    // Set initial value to BLACK = 0,
    // Scan the addtional interger, which decides shade.
    // Return shade_number which is an int value.
    int shade_number = BLACK; 
    if (command_number == COLOURED_COMMAND) {
        scanf("%d", &shade_number); 
    }
        
    return shade_number;  
}

// Stage1 && Stage2.
//
// Draw line & diagonas.
//
// Draw horizontal and vertical lines.
// Set the colour of the relevant elements in the canvas array.
//
// Draw diagonal lines that are on a 45 degree angle.
void draw_line(
    int canvas[N_ROWS][N_COLS], 
    int command_number, 
    int shade_index
) { 
 
    if (command_number == DRAW_LINE_COMMAND) {
        int start_row, 
            start_col, 
            end_row, 
            end_col;
        
        scanf(
            "%d %d %d %d", 
            &start_row, 
            &start_col, 
            &end_row, 
            &end_col
        ); 
          
        // Determine whether the parameters meet the conditions.
        // ONLY let valid parameters go through. 
        if (
            (start_row < 0 && end_row >= N_ROWS) 
            || (end_row < 0 && start_row >= N_ROWS) 
            || (start_row < 0 && end_row < 0)
            || (start_col < 0 && end_col < 0)
            || (end_row >= N_ROWS && start_row >= N_ROWS)
            || (end_col >= N_COLS && start_col >= N_COLS) 
            || (start_col < 0 && end_col >= N_COLS)
            || (end_col < 0 && start_col >= N_COLS)
        ) {
            return;
        } 
        
        // If row and col are both out of range,
        // adjust them to diagonal form.
        //        
        // Top right side.
        while (start_row <= 0 && start_col > N_COLS - 1) {
            start_row++;
            start_col--;
        }        
        // Top left side.
        while (start_row < 0 && start_col < 0) {
            start_row++;
            start_col++;
        }        
        // Bot right side.
        while (start_row > N_ROWS - 1 && start_col > N_COLS - 1) {
            start_row--;
            start_col--;
        }        
        // Bot left side.
        while (start_row > N_ROWS - 1 && start_col <= 0) {
            start_row--;
            start_col++;
        }
        
        // For end_col and end_row.
        while (end_row <= 0 && end_col > N_COLS - 1) {
            end_row++;
            end_col--;
        }
        while (end_row <= 0 && end_col <= 0) {
            end_row++;
            end_col++;
        }
        while (end_row > N_ROWS - 1 && end_col > N_COLS - 1) {
            end_row--;
            end_col--;
        }
        while (end_row > N_ROWS - 1 && end_col <= 0) {
            end_row--;
            end_col++;
        }
        
        // If after previous adjustments, 
        // one of col or row still out of range.
        // Adjust it to valid 0->19 && 0->35.
        if (start_row < 0) {
            start_row = 0;
        } else if (start_row >= N_ROWS) {
            start_row = N_ROWS - 1;
        }

        if (end_row < 0) {
            end_row = 0;
        } else if (start_row >= N_ROWS) {
            end_row = N_ROWS - 1;
        }

        if (start_col < 0) {
            start_col = 0;
        } else if (start_col >= N_COLS) {
            start_col = N_COLS - 1;
        }

        if (end_col < 0) {
            end_col = 0;
        } else if (end_col >= N_COLS) {
            end_col = N_COLS - 1;
        }
   
        // Draw Line.
        // Horizontal lines.
        // Left to right && right to left.
        if (start_row == end_row) {        
            while (start_col < end_col) {
                canvas[start_row][start_col] = shade_index;
                start_col++;
            }            
            while (start_col >= end_col) {
                canvas[start_row][start_col] = shade_index;
                start_col--;
            }
        } 
        
        // Vertical lines.
        // Top to bot && bot to top.
        else if (start_col == end_col) {
            while (start_row < end_row) {
                canvas[start_row][start_col] = shade_index;
                start_row++;
            }
            while (start_row >= end_row) {
                canvas[start_row][start_col] = shade_index;
                start_row--;
            }
        }
        
        // Draw Diagonal.
        //
        // If absolute valuse of the difference of rows 
        // and the difference of cols are equal. 
        // Then gradient = 1, it is a diagonal.
        if (abs(start_row - end_row) == abs(start_col - end_col)) {
        
            // Top left to bot right.
            while (start_row < end_row && start_col < end_col) {
                canvas[start_row][start_col] = shade_index;
                start_row++;
                start_col++;
            }            
            // Bot left to top right.
            while (start_row < end_row && start_col > end_col) {
                canvas[start_row][start_col] = shade_index;
                start_row++;
                start_col--;
            }            
            // Top right to bot left
            while (start_row > end_row && start_col < end_col) {
                canvas[start_row][start_col] = shade_index;
                start_row--;
                start_col++;
            }            
            // Bot right to top left.
            while (start_row > end_row && start_col > end_col) {
                canvas[start_row][start_col] = shade_index;
                start_row--;
                start_col--;
            }            
            // When rows are equal and cols are equal,
            // print a coordinate = pixel.
            while (start_row == end_row && start_col == end_col) {
                canvas[start_row][start_col] = shade_index;
                return;
            }
        }
    }                  
}

// Stage1.
//
// Draw rectangles.
//
// Draw rectangles.
// Colour all the pixels in the rectangle 
// formed by the two corners start and end.
void fill_rectangle(
    int canvas[N_ROWS][N_COLS], 
    int command_number, 
    int shade_index
) {

    if (command_number == RECTANGLE_COMMAND) {
        int start_row, 
            start_col, 
            end_row, 
            end_col;
        
        scanf(
            "%d %d %d %d", 
            &start_row, 
            &start_col, 
            &end_row, 
            &end_col
        ); 
        
        // Set sets of saved_values to store the values,
        // in order to avoid some values might be changed in some process.
        int saved_value1 = start_row;
        int saved_value2 = end_row;
        int saved_value3 = start_col;
        int saved_value4 = end_col;
        
        // Do nothing, when both the start and end are out of range.
        if (
            (saved_value1 < 0 && saved_value2 >= N_ROWS) 
            || (saved_value2 < 0 && saved_value1 >= N_ROWS) 
            || (saved_value2 < 0 && saved_value1 < 0)
            || (saved_value4 < 0 && saved_value3 < 0) 
            || (saved_value2 >= N_ROWS && saved_value1 >= N_ROWS)
            || (saved_value4 >= N_COLS && saved_value3 >= N_COLS) 
            || (saved_value3 < 0 && saved_value4 >= N_COLS)
            || (saved_value4 < 0 && saved_value3 >= N_COLS)
        ) {
            return;
        }
        
        // Adjust the initial value, 
        // if ONLY column or row is out of range.
        // For example, when row = -1, adjust it to 0,
        // when column = 40, adjust it to 35 (0 -> 35 = 36).
        if (saved_value1 <= 0) {
            saved_value1 = 0;
        } else if (saved_value1 >= N_ROWS) {
            saved_value1 = N_ROWS - 1;
        }        
        if (saved_value2 <= 0) {
            saved_value2 = 0;
        } else if (saved_value2 >= N_ROWS) {
            saved_value2 = N_ROWS - 1;
        }        
        if (saved_value3 <= 0) {
            saved_value3 = 0;
        } else if (saved_value3 >= N_COLS) {
            saved_value3 = N_COLS - 1;
        }         
        if (saved_value4 <= 0) {
            saved_value4 = 0;
        } else if (saved_value4 >= N_COLS) {
            saved_value4 = N_COLS - 1;
        }    
        
        // Now inputs all valid, 
        // Creat a rectangle with row from start_row to end_row
        // and column from start_col to end_col.
        start_row = saved_value1;
        end_row = saved_value2;
        while (start_row <= end_row) {
        
            start_col = saved_value3;
            end_col = saved_value4;
            while (start_col < end_col) {
                canvas[start_row][start_col] = shade_index;
                start_col++;
            }            
            while (start_col >= end_col) {
                canvas[start_row][start_col] = shade_index;
                start_col--;
            }
            
            start_row++;
        }

        // Reset start_row and start_col 
        // by using saved_value1 and saved_value2,
        // because their values have changed.
        start_row = saved_value1;
        end_row = saved_value2;
        while (start_row >= end_row) {
        
            start_col = saved_value3;
            end_col = saved_value4;
            while (start_col < end_col) {
                canvas[start_row][start_col] = shade_index;
                start_col++;
            }
            while (start_col >= end_col) {
                canvas[start_row][start_col] = shade_index;
                start_col--;
            }
            
            start_row--;
        }
    }     
}

// Draw line & diagonas1.
//
// Draw horizontal and vertical lines.
// Set the colour of the relevant elements in the canvas array.
//
// Draw diagonal lines that are on a 45 degree angle.
//
// This is used to ahieve Stage 4 - Macro playback.
void draw_line1(
    int canvas[N_ROWS][N_COLS], 
    int command_number, 
    int start_row, 
    int start_col, 
    int end_row, 
    int end_col, 
    int shade_index
) { 
    if (command_number == DRAW_LINE_COMMAND) {
 
        // Determine whether the parameters meet the conditions.
        // ONLY let valid parameters go through.
        if (
            (start_row < 0 && end_row >= N_ROWS) 
            || (end_row < 0 && start_row >= N_ROWS) 
            || (start_row < 0 && end_row < 0)
            || (start_col < 0 && end_col < 0)
            || (end_row >= N_ROWS && start_row >= N_ROWS)
            || (end_col >= N_COLS && start_col >= N_COLS) 
            || (start_col < 0 && end_col >= N_COLS)
            || (end_col < 0 && start_col >= N_COLS)
        ) {
            return;
        } 
        
        // If row and col are both out of range,
        // adjust them to diagonal form.
        //
        // Top right side.
        while (start_row <= 0 && start_col > N_COLS - 1) {
            start_row++;
            start_col--;
        }        
        // Top left side.
        while (start_row < 0 && start_col < 0) {
            start_row++;
            start_col++;
        }        
        // Bot right side.
        while (start_row > N_ROWS - 1 && start_col >  N_COLS - 1) {
            start_row--;
            start_col--;
        }        
        // Bot left side.
        while (start_row > N_ROWS - 1 && start_col <= 0) {
            start_row--;
            start_col++;
        }
                
        // For end_col and end_row.
        while (end_row <= 0 && end_col >  N_COLS - 1) {
            end_row++;
            end_col--;
        }        
        while (end_row <= 0 && end_col <= 0) {
            end_row++;
            end_col++;
        }        
        while (end_row > N_ROWS - 1 && end_col >  N_COLS - 1) {
            end_row--;
            end_col--;
        }        
        while (end_row > N_ROWS - 1 && end_col <= 0) {
            end_row--;
            end_col++;
        }
        
        // If after previous adjustments, 
        // one of col or row still out of range.
        // Adjust it to valid 0 -> 19 && 0 -> 35.
        if (start_row < 0) {
            start_row = 0;
        } else if (start_row >= N_ROWS) {
            start_row = N_ROWS - 1;
        }
        if (end_row < 0) {
            end_row = 0;
        } else if (start_row >= N_ROWS) {
            end_row = N_ROWS - 1;
        }
        if (start_col < 0) {
            start_col = 0;
        } else if (start_col >= N_COLS) {
            start_col = N_COLS - 1;
        }
        if (end_col < 0) {
            end_col = 0;
        } else if (end_col >= N_COLS) {
            end_col = N_COLS -1;
        }
   
        // Draw Line.
        // Horizontal lines.
        // Left to right && right to left.
        if (start_row == end_row) {
            while (start_col < end_col) {
                canvas[start_row][start_col] = shade_index;
                start_col++;
            }
            while (start_col >= end_col) {
                canvas[start_row][start_col] = shade_index;
                start_col--;
            }
        } 
        
        // Vertical lines.
        // Top to bot && bot to top.
        else if (start_col == end_col) {        
            while (start_row < end_row) {
                canvas[start_row][start_col] = shade_index;
                start_row++;
            }            
            while (start_row >= end_row) {
                canvas[start_row][start_col] = shade_index;
                start_row--;
            }
        }
        
        // Draw diagonal.
        //
        // If absolute valuse of the difference of rows 
        // and the difference of cols are equal. 
        // Then gradient = 1, it is a diagonal.
        if (abs(start_row - end_row) == abs(start_col - end_col)) {
        
            // Top left to bot right.
            while (start_row < end_row && start_col < end_col) {
                canvas[start_row][start_col] = shade_index;
                start_row++;
                start_col++;
            }            
            // Bot left to top right.
            while (start_row < end_row && start_col > end_col) {
                canvas[start_row][start_col] = shade_index;
                start_row++;
                start_col--;
            }           
            // Top right to bot left
            while (start_row > end_row && start_col < end_col) {
                canvas[start_row][start_col] = shade_index;
                start_row--;
                start_col++;
            }           
            // Bot right to top left.
            while (start_row > end_row && start_col > end_col) {
                canvas[start_row][start_col] = shade_index;
                start_row--;
                start_col--;
            }
        }
    }                  
}

// Draw rectangle1.
//
// Draw rectangles.
// Colour all the pixels in the rectangle 
// formed by the two corners start and end.
//
// This is used to ahieve Stage 4 - Macro playback.
void fill_rectangle1(
    int canvas[N_ROWS][N_COLS], 
    int command_number, 
    int start_row, 
    int start_col, 
    int end_row, 
    int end_col,
    int shade_index
) {

    if (command_number == RECTANGLE_COMMAND) {
       
        // Set sets of saved_values to store the values,
        // in order to avoid some values might be changed in some process.
        int saved_value1 = start_row;
        int saved_value2 = end_row;
        int saved_value3 = start_col;
        int saved_value4 = end_col;
        
        // Do nothing, when both the start and end are out of range.
        if (
            (saved_value1 < 0 && saved_value2 >= N_ROWS) 
            || (saved_value2 < 0 && saved_value1 >= N_ROWS) 
            || (saved_value2 < 0 && saved_value1 < 0)
            || (saved_value4 < 0 && saved_value3 < 0) 
            || (saved_value2 >= N_ROWS && saved_value1 >= N_ROWS)
            || (saved_value4 >= N_COLS && saved_value3 >= N_COLS) 
            || (saved_value3 < 0 && saved_value4 >= N_COLS)
            || (saved_value4 < 0 && saved_value3 >= N_COLS)
        ) {
            return;
        }
        
        // Adjust the initial value, 
        // if ONLY column or row is out of range.
        // For example, when row = -1, adjust it to 0,
        // when column = 40, adjust it to 35 (0 -> 35 = 36).
        if (saved_value1 <= 0) {
            saved_value1 = 0;
        } else if (saved_value1 >= N_ROWS) {
            saved_value1 = N_ROWS - 1;
        }        
        if (saved_value2 <= 0) {
            saved_value2 = 0;
        } else if (saved_value2 >= N_ROWS) {
            saved_value2 = N_ROWS - 1;
        }        
        if (saved_value3 <= 0) {
            saved_value3 = 0;
        } else if (saved_value3 >= N_COLS) {
            saved_value3 = N_COLS - 1;
        }         
        if (saved_value4 <= 0) {
            saved_value4 = 0;
        } else if (saved_value4 >= N_COLS) {
            saved_value4 = N_COLS - 1;
        }    
        
        // Now inputs all valid, 
        // Creat a rectangle with row from start_row to end_row
        // and column from start_col to end_col.
        start_row = saved_value1;
        end_row = saved_value2;
        while (start_row <= end_row) {
        
            start_col = saved_value3;
            end_col = saved_value4;
            while (start_col < end_col) {
                canvas[start_row][start_col] = shade_index;
                start_col++;
            }            
            while (start_col >= end_col) {
                canvas[start_row][start_col] = shade_index;
                start_col--;
            }
            
            start_row++;
        }

        // Reset start_row and start_col 
        // by using saved_value1 and saved_value2,
        // because their values have changed.
        start_row = saved_value1;
        end_row = saved_value2;
        while (start_row >= end_row) {
        
            start_col = saved_value3;
            end_col = saved_value4;
            while (start_col < end_col) {
                canvas[start_row][start_col] = shade_index;
                start_col++;
            }
            while (start_col >= end_col) {
                canvas[start_row][start_col] = shade_index;
                start_col--;
            }
            
            start_row--;
        }      
    }     
}

// Displays the canvas, by printing the integer value stored in
// each element of the 2-dimensional canvas array.
//
// You should not need to change the displayCanvas function.
void display_canvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            printf("%d ", canvas[row][col]);
            col++;
        }
        row++;
        printf("\n");
    }
}

// Sets the entire canvas to be blank, by setting each element in the
// 2-dimensional canvas array to be WHITE (which is #defined at the top
// of the file).
//
// You should not need to change the clearCanvas function.
void clear_canvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            canvas[row][col] = WHITE;
            col++;
        }
        row++;
    }
}



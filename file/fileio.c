
#include "fileio.h"

void bad_file(char *where)
{
    fprintf(stderr, "File error in %s\n", where);
    exit(1);
}

// Graciously adapted from a solution posted here:
// https://stackoverflow.com/questions/8286668/how-to-read-mnist-data-in-c
int reverse_int(int i) 
{
    unsigned char c1, c2, c3, c4;

    // Extract first 8 bits, next 8 bits, and so on
    c1 = (i >>  0) & 255;
    c2 = (i >>  8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    // Set first 8 bits to the last 8 bits, and so on
    return ((int) c1 << 24) + ((int) c2 << 16) + ((int) c3 << 8) + c4;
}

void read_int(FILE *file, int *x)
{
    fread(x, sizeof(int), 1, file);
    *x = reverse_int(*x);
}

int open_files(char *image_path, char *label_path)
{
    image_file = fopen(image_path, "r");
    label_file = fopen(label_path, "r");

    printf("%d\n%d\n", !image_file, !label_file);
    
    // Returns true if both successful, false otherwise.
    return !(!image_file || !label_file);
}

void close_files()
{
    fclose(image_file);
    fclose(label_file);
}

Example *create_example(int rows, int cols)
{
    Example *example = malloc(sizeof(Example));
    if (!example)
        bad_mem("create_example()");

    example->image = matrix_build(rows * cols, 1);
    example->label = -1;

    return example;
}

Example *training_data_read()
{
    int opened = open_files("./data/train-images-idx3-ubyte",
                            "./data/train-labels-idx1-ubyte");

    if (!opened)
        bad_file("training_data_read()");

    int num_examples = 0;
    int rows, cols;
    int int_buffer;

    unsigned char ubyte_buffer;

    // Magic number in label file
    read_int(label_file, &int_buffer);
    // Num examples
    read_int(label_file, &num_examples);
    // Label file stream is now at first label

    // Magic number in image file
    read_int(image_file, &int_buffer);
    // Num examples, but discarding because we already got this number above
    read_int(image_file, &int_buffer);

    // Num rows, cols
    read_int(image_file, &rows);
    read_int(image_file, &cols);
    // Image file stream is now at first pixel of first image

    Example * examples = (Example *) malloc(num_examples * sizeof(Example));
    if (!examples)
        bad_mem("training_data_read()");

    for (int i = 0; i < num_examples; i++)
    {
        // Read label for this example
        fread(&examples[i].label, sizeof(unsigned char), 1, label_file);
        examples[i].image = matrix_build(rows, cols);

        // Copy image data into the matrix for this example
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                fread(&ubyte_buffer, sizeof(unsigned char), 1, image_file);
                examples[i].image->entries[row][col] = ubyte_buffer;
            }
        }
    }

    return examples;
}
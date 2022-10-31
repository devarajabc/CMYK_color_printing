#include <stdio.h>
#include <math.h>
#define MAX_SIZE 256

unsigned int W, H;
unsigned int image[MAX_SIZE][MAX_SIZE] = {0};

char layers[4] = {'C', 'M', 'Y', 'K'};

void print_C(unsigned int mask[][MAX_SIZE]);
void print_M(unsigned int mask[][MAX_SIZE]);
void print_Y(unsigned int mask[][MAX_SIZE]);
void print_K(unsigned int mask[][MAX_SIZE]);
void CMYK_to_RGB();

int main()
{
    // Get the dimension of the image.
    scanf("%u %u", &W, &H);

    // Declare the mask for single ink color.
    unsigned int mask[MAX_SIZE][MAX_SIZE] = {0};

    // For each layer, do the following:
    for (int layer = 0; layer < 4; ++layer)
    {
        // Get color mask.
        for (int i = 0; i < H; ++i)
        {
            for (int j = 0; j < W; ++j)
            {
                scanf("%u", &mask[i][j]);
            }
        }

        // Print a layer of that color to the paper.
        switch (layers[layer])
        {
            case 'C': print_C(mask); break;
            case 'M': print_M(mask); break;
            case 'Y': print_Y(mask); break;
            case 'K': print_K(mask); break;
        }
    }

    // Convert CMYK color to RGB color.
    CMYK_to_RGB();

    // Show the final result.
    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            printf("#%06x ", image[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void print_C(unsigned int mask[][MAX_SIZE])
{
    for(int i=0;i<H;i++)
    {
        for(int j=0;j<W;j++)
        {
            image[i][j]=mask[i][j];
            image[i][j]<<=8;
        }
    }

}

void print_M(unsigned int mask[][MAX_SIZE])
{
    for(int i=0;i<H;i++)
    {
        for(int j=0;j<W;j++)
        {
            image[i][j]|=mask[i][j];
            image[i][j]<<=8;
        }
    }
}

void print_Y(unsigned int mask[][MAX_SIZE])
{
    for(int i=0;i<H;i++)
    {
        for(int j=0;j<W;j++)
        {
            image[i][j]|=mask[i][j];
            image[i][j]<<=8;//留給下一個
        }
    }
}

void print_K(unsigned int mask[][MAX_SIZE])
{
    for(int i=0;i<H;i++)
    {
        for(int j=0;j<W;j++)
        {
            image[i][j]|=mask[i][j];
        }
    }
}
//image 的輸入沒問題
void CMYK_to_RGB()
{
    for(int i=0;i<H;i++)
    {
        for(int j=0;j<W;j++)
        {
           unsigned int temp=0;
           unsigned int babo=0xff;
           //R = 255 × (100 - C)% × (100 - K)%
           temp=lround(255*(100-(image[i][j]>>3*8))/100.0*(100-image[i][j]&babo)/100.0);
           temp<<=8;
           temp|=lround(255*(100-((image[i][j]&(babo<<2*8))>>2*8))/100.0*(100-image[i][j]&babo)/100.0);
           temp<<=8;
           temp|=lround(255*(100-((image[i][j]&(babo<<8))>>8))/100.0*(100-image[i][j]&babo)/100.0);
           image[i][j]=temp;
        }
    }

}


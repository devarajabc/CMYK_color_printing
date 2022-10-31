# CMYK_color_printing

3
Home
>
Problems
>
CMYK color printing
CMYK color printing
hard
Pass rate: 96.97% (96/99)
人類在感知顏色時，會因為不同色光的佔比不同，而感受到不同的顏色。人眼的結構對於紅光、綠光與藍光三個波段的光線最為敏感，因此我們稱紅色、綠色與藍色為光的三原色，其他顏色的色光都可以透過紅綠藍三種原色光依不同比例混合而得到。



彩色顯示器之所以可以顯示五顏六色的色彩，靠的便是色光混合的原理。顯示器由上千萬個小格子組成，每一個格子內都有紅綠藍三種顏色的極小型 LED 燈泡。透過調整各個單色燈泡的亮度，就可以在一個格子內發出某個特定顏色的光，不同格子內各自發出特定顏色的光，遠遠看起來就形成了一個影像。

為了硬體實作上的方便，彩色顯示器通常會把單一色光可以顯示的亮度區分為 256 個區段，全暗表示為 0，全亮表示為 255，因此單一色光的亮度，便可以用 8 個 bits 來表示。三種色光各使用 8 個 bits，總共加起來就是 24 個 bits，因此，當電腦要表示一個顏色的時候，可以使用一個 24 bits 的資料來表示。我們通常會使用三個二位數十六進制數字來表示這樣的 24 bits 資料，第一個數字代表紅光的亮度，第二個代表綠光，第三個代表藍光，數值為 00 時代表該色光全暗，數值為 FF (255) 時代表該色光全亮。例如： #FF0000 即是正紅色的意思，而 CK Judge 網頁背景的深藍色則是 #1E2226。這樣的色彩表示方法，稱為 RGB 十六進制色碼。

但是，當我們要把影像列印到白紙上時，由於白紙不會發光，因此我們也就無法透過 RGB 色碼來告訴印表機要輸出什麼顏色了。在進行彩色印刷時，我們使用的是 CMYK 四分色的方式來描述彩色的圖像。CMYK 指的是四種不同顏料的顏色，其中 C 是青色 (Cyan)、M 是洋紅色 (Magenta)、Y 是黃色 (Yellow)，K 則是黑色 (blacK)。白紙因為能反射所有顏色的色光，因此看起來是白色的，而當青色顏料覆蓋在白紙上時，會阻斷被覆蓋區域反射紅光的能力，因此才會看起來像是剩下的兩個三原色光：綠光與藍光混合出來的青色。同樣道理，洋紅色顏料會阻斷白紙反射綠光的能力，因此看起來像是紅光與藍光混合的洋紅色；黃色顏料會阻斷白紙反射藍光的能力，因此看起來像是紅光與綠光混合的黃色。照理來說三個顏色混合起來應該要是黑色，但實際上有色顏料並沒有辦法百分之百阻斷色光反射，因此通常會再另外使用黑色的顏料對想要印成黑色的區域進行覆蓋。

在進行套色時，我們會將一張彩色圖片區分成 C, M, Y, K 四個顏色的圖層，每個圖層只由一種顏色的墨水列印，然後決定各圖層的每一個像素要覆蓋上多少比例的墨水，其中 0% 表示不覆蓋（白色），100% 代表完全覆蓋。在印刷完四個顏色的圖層後，就會形成一張彩色圖像。因此，在進行彩色印刷的時候，我們可以用四個百分比數字來描述一個顏色。例如：正紅色可以用 (0%, 100%, 100%, 0%) 來表達，#1E2226 則可以用 (21%, 10%, 0%, 85%) 來表達。

Everything You Need to Know About CMYK Printing

我們可以用以下的公式將 CMYK 顏色轉換成 RGB 顏色：

R = 255 × (100 - C)% × (100 - K)%
G = 255 × (100 - M)% × (100 - K)%
B = 255 × (100 - Y)% × (100 - K)%
其中，R, G, B 的值域為 [0, 255]；C, M, Y, K 的定義域為 [0, 100]。由於牽涉到浮點數的乘法，計算結果應為四捨五入後的整數，因此你可以使用 <math.h> 函式庫內的 lround() 函式取得精確的計算結果。

在本題當中，讓我們來模擬彩色印表機列印彩色圖像的過程。給定一張圖片的寬 W 與高 H，以及這張圖片的 CMYK 四個色層的墨水分配 mask，請紀錄這張圖片的四個色層，然後將這張圖片以 RGB 十六進制色碼輸出。

Humans can distinguish colors based upon the different combination of the light of different wavelendth. Human eye is more responsive to light that is perceived as red, green and blue. Therefore, color red, green and blue are known as the (additive) primary colors. We can obtain any color by mixing RGB colors light with different proportion.



The additive color mixing technique is used on color display (screen) to display colorful graph. A color display consists of millions of pixels, each pixel is further composed of 3 tiny LEDs with color red, green and blue respectively. By adjusting the brightness of each LED, a pixel can emit light in any color. With different pixel displaying different color, an colorful image is formed on the screen.

For the simplification of the hardware, the brightness of a color LED is usually devided into 256 stages, with stage 0 being completely dark (black), and stage 255 being completely bright. Therefore, we can use an 8-bits data to describe the brightness of a LED. Since each pixel is composed of 3 LEDs, we need 24 bits in total to describe the color of a pixel. Usually, the 24-bits data is written in a 6-digits hexadecimal number, with the first 2 digits representing brightness of color red, the second 2 digits representing green, and the last 2 digits representing blue. If the value is 00, it means that color is completely dark; if the value is FF (255), it means that color is completely bright. For example: #FF0000 is true red, and the background color of CK Judge webpages is #1E2226. This color representation is called RGB HEX color code.

Using RGB HEX color code to describe color on a monitor is quite straightforward, but it becomes inadvisable when we want to describe printed colors, since the paper do not emit light. In color printing, we use CMYK color model to describe colors. CMYK refers to the 4 ink colors used in color printing: Cyan, Magenta, Yellow, and blacK. A white paper looks white since it reflects all the colors of light. When we cover white paper with some cyan ink, the covered area won't reflect the red light, and the color of that area is therefore looks like cyan (green + blue). Similarly, the area covered with magenta ink looks magenta (red + blue) since it doesn't reflect green light, and the area covered with yellow ink looks yellow (red + green) since it doesn't reflect blue light. Ideally, if we cover an area with all these 3 color, it should become black. But since inks are unable to completely block the reflection of light, additional black ink is required to print color black properly.

When printing, a colorful image is decomposed into 4 single color layers C, M, Y, K. In each layer, each pixel is covered with ink with certain proportion, where 0% means no ink covered (white), and 100% means fully covered. After 4 colors are all printed, it becomes a colorful picture, as the following figure illustrates. With this in mind, we can use 4 percentages to describe a CMYK color. For example, true red can be describe as (0%, 100%, 100%, 0%), and #1E2226 can be described as (21%, 10%, 0%, 85%).

Everything You Need to Know About CMYK Printing

We can use following equations to convert CMYK color to RGB HEX color code:

R = 255 × (100 - C)% × (100 - K)%
G = 255 × (100 - M)% × (100 - K)%
B = 255 × (100 - Y)% × (100 - K)%
The range of R, G, B is [0, 255], and the range of C, M, Y, K is [0, 100]. This calculation revolves floating number multiplication, and the result should be rounded to the nearest integer. You can use lround() function defined in <math.h> to get the precise result.

In this problem, let simulate the CMKY color printing process. Given the width W and height H of an image, and 4 CMYK color layers mask of that image, please record these layers and output the image in RGB HEX color code.

Input
第一行為兩個整數，分別代表該圖片的寬 `W` 與高 `H`。

接下來會有四個 H x W 的矩陣，分別代表 C, M, Y, K 四個顏色的圖層，該矩陣中每一個數字的值皆於 [0, 100] 範圍中。

The first line contains 2 integer, which is the width `W` and the height `H` of the image.

And it follows by 4 H x W matrics, representing 4 color layer C, M, Y, K. Each element of the matrics is in range [0, 100].

Output
一個 H x W 的矩陣，每一個元素皆為 RGB 十六進制色碼 #RRGGBB。請參考範例輸出。

A H x W matrix with each element being RGB HEX color code #RRGGBB. Please refer to sample case.

Loader Code
Your code will be judge using this program:

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
Example 1

Input

1 1

21

10

0

85

Output

#1e2226 

Example 2

Input

4 2

100 0 0 0
0 100 100 0

0 100 0 0
100 0 100 0

0 0 100 0
100 100 0 0

0 0 0 100
0 0 0 0


Output

#00ffff #ff00ff #ffff00 #000000 
#ff0000 #00ff00 #0000ff #ffffff 

Example 3

Input

5 5

50 44 37 16 30 
9 96 43 1 5 
60 6 66 90 37 
80 13 2 19 8 
23 56 0 7 32 

87 72 59 18 27 
36 55 36 22 98 
96 64 71 47 64 
60 6 18 68 99 
100 88 38 27 43 

39 40 81 68 94 
99 63 8 2 67 
98 46 88 35 13 
30 82 11 20 67 
7 26 27 55 70 

30 12 52 17 11 
60 43 71 65 76 
89 54 77 86 12 
71 41 39 0 30 
14 23 40 77 6 


Output

#59176d #7e3f87 #4d3217 #b2ae44 #9fa60e 
#5d4101 #064136 #2a2f44 #584657 #3a0114 
#0b0101 #6e2a3f #141107 #041317 #8d51c3 
#0f1e34 #838d1b #98808a #cf52cc #a4023b 
#a900cc #561891 #995f70 #372b1a #a38948 

Limits


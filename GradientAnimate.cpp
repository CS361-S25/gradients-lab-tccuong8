#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"
#include "emp/math/math.hpp"

// You’ll also always need a Document as a global variable:
emp::web::Document doc{"target"};

// Now declare your GradientAnimator class that inherits from emp::web::Animate. If you don’t remember that syntax, feel free to check the Neighbor Finder lab.
class GradientAnimate : public emp::web::Animate
{

    // You’ll again need a Canvas to draw on and a constructor for your class. Create those now (and check the previous lab if you aren’t sure what to do). Also send your canvas to your document with the <<.
    emp::web::Canvas canvas{2500, 2500, "canvas"};

public:
    // You’ll again need a Canvas to draw on and a constructor for your class. Create those now (and check the previous lab if you aren’t sure what to do). Also send your canvas to your document with the <<.
    // int number = 0;
    float value = 0;

    // Create an instance variable that is a vector of vectors of floats:
    std::vector<std::vector<float>> cells;
    std::vector<std::vector<float>> next;

    // In the constructor for you animator, set the number of cells you want in the width (num_w_boxes in the example) and height (num_h_boxes in the example) and set them all to start with 0:
    int num_w_boxes;
    int num_h_boxes;

    GradientAnimate()
    {
        // Since we’ll be aiming to animate this time, you’ll want some buttons to control turning the animation on and going one step at a time. Fortunately, Empirical provides built-in buttons for just those purposes that are already hooked up to control the animation once you put them in your document:
        doc << GetToggleButton("Toggle");
        doc << GetStepButton("Step");
        doc << canvas;

        num_w_boxes = 10;
        num_h_boxes = 10;
        cells.resize(num_w_boxes, std::vector<float>(num_h_boxes, 1.0));
        next.resize(num_w_boxes, std::vector<float>(num_h_boxes, 1.0));
        for (int i = 0; i < num_h_boxes; i++)
        {
            next[0][i] = 0.0;
        }
        // next[1][2] = 1;
    }

    // Next you need a DoFrame method, which is what is called at each step of the animation. This is a void method that takes no parameters.
    void DoFrame()
    {
        // In your DoFrame method, you will eventually draw some shapes, but to get a basic idea of how it works, create a instance variable (up above the constructor) to just hold a number.  In DoFrame, first clear the canvas with canvas.Clear();, then increment your number variable. Then add a Text object to your canvas with your number:
        canvas.Clear();
        // number++;
        // canvas.Text(*new emp::Point(10,10), std::to_string(number));

        // Get rid of the incrementing number and instead draw a rectangle on your canvas with the color specified as a shade of grey using HSV. HSV stands for hue, saturation, and value. You can get somewhat of a greyscale by having the value go from 0 to 1.
        // The new value should be the minimum between it being incremented by 0.01 and 1.0. You can use the std::min function to do this.
        // value = std::min(value + 0.01, 1.0);

        // Make sure that you are getting a grey rectangle and then try changing your code so that the rectangle gets slightly darker or lighter each step. You will eventually get an assert error when you go beyond 0 to 1, but don’t worry about that right now.
        // canvas.Rect(10, 10, 100, 100, emp::ColorHSV(0, 0, value), "black");
        // canvas.Text(*new emp::Point(10,120), std::to_string(value));
        // In DoFrame make a nested set of for-loops that go through all your cells and draw a rectangle using the ColorHSV argument, similar to how you did for the Neighbor Finder Lab, but with the color being based on the cell value instead. Make sure to compile and run to make sure that you see your grid of cells.
        for (int i = 0; i < num_w_boxes; i++)
        {
            for (int j = 0; j < num_h_boxes; j++)
            {
                // You probably want to make a couple of the cells a different value to start. In your constructor, set a few of them to be something other than 0 and make sure that that shows up correctly when you compile and run.
                // value = std::min(value + 0.01, 1.0);
                cells[i][j] = next[i][j];
                canvas.Rect(i * 50, j * 50, 50, 50, emp::ColorHSV(0, 0, cells[i][j]), "black");
            }
        }

        // You’re now ready to set an update rule so that your cell values change each step. There are an infinite number of rules that you could try. Start out by doing something simple like getting the shade to just move horizontally across the screen and then falling off the edge (by having the new cell value determined by its immediate neighbor).
        // First, update the leftmost column for all rows:
        // for (int j = 0; j < num_h_boxes; j++)
        // {
        //     next[0][j] = std::min(cells[0][j] + 0.1, 1.0);
        // }

        // Then, for every other column, get the value from the column to its left.
        for (int i = 0; i < num_w_boxes; i++)
        {
            int prevX = emp::Mod((i - 1), num_w_boxes);
            for (int j = 0; j < num_h_boxes; j++)
            {
                // int nextX = emp::Mod((i + 1), num_w_boxes);
                if (cells[prevX][j] == 0.0){
                    next[i][j] = 0.0;
                }
                else{
                    next[i][j] = std::min(cells[i][j] + 0.1, 1.0);
                }
            }
        }
    }
};

GradientAnimate animate;

// After your class, you’ll need to create an instance of your class and make a main method that calls the Step() method of your class.
int main()
{
    animate.Step();
}

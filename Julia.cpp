#include "Julia.h"
#include <fstream>

const int WIDTH = 2048 * 2;
const int HEIGHT = 1024 * 2;
uint32_t image[HEIGHT][WIDTH];
//write tga function taken from labs 
void write_tga(const char* filename)
{
    ofstream outfile(filename, ofstream::binary);

    uint8_t header[18] = {
        0, // no image ID
        0, // no colour map
        2, // uncompressed 24-bit image
        0, 0, 0, 0, 0, // empty colour map specification
        0, 0, // X origin
        0, 0, // Y origin
        WIDTH & 0xFF, (WIDTH >> 8) & 0xFF, // width
        HEIGHT & 0xFF, (HEIGHT >> 8) & 0xFF, // height
        24, // bits per pixel
        0, // image descriptor
    };
    outfile.write((const char*)header, 18);

    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            uint8_t pixel[3] = {
                image[y][x] & 0xFF, // blue channel
                (image[y][x] >> 8) & 0xFF, // green channel
                (image[y][x] >> 16) & 0xFF, // red channel
            };
            outfile.write((const char*)pixel, 3);
        }
    }

    outfile.close();
    if (!outfile)
    {
        // An error has occurred at some point since we opened the file.
        cout << "Error writing to " << filename << endl;
        exit(1);
    }
}
//amp functions for Julia set maths 
float c_abs(Complex1 c) restrict(cpu, amp)
{
    return concurrency::fast_math::sqrt(c.x * c.x + c.y * c.y);
}// c_abs
Complex1 c_add(Complex1 a, Complex1 b) restrict(cpu, amp) // restrict keyword - able to execute this function on the GPU and CPU
{
    Complex1 c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}// c_add
Complex1 c_mul(Complex1 c1, Complex1 c2) restrict(cpu, amp)
{
    Complex1 tmp;
    float a = c1.x;
    float b = c1.y;
    float c = c2.x;
    float d = c2.y;
    tmp.x = a * c - b * d;
    tmp.y = b * c + a * d;
    return tmp;
}// c_mu
double mod(Complex1 a) restrict(cpu, amp) {
    return sqrt(a.x * a.x + a.y * a.y);
}

//make image relitve to raidius
Complex1 mapPoint(int width, int height, double radius, int x, int y) restrict(cpu, amp) {
    Complex1 c;
    int l = (width < height) ? width : height;

    c.x = 2 * radius * (x - width / 2.0) / l;
    c.y = 2 * radius * (y - height / 2.0) / l;

    return c;

}

//juila set in amp tile sizes 4 through to 32 same cade in ech otherwise
void Julia::compute_JULIA_tile4(int width, int height, Complex1 c, double radius, int n) {
    //tile size 
    const int TS = 4;

    //copy image
    uint32_t* in_Image = &(image[0][0]);

    //create loacl varible for image data
    concurrency::array_view<uint32_t, 2> imDAT(HEIGHT, WIDTH, in_Image);

    //clear any data in it
    imDAT.discard_data();

    //start threads
    concurrency::parallel_for_each(imDAT.extent.tile<TS, TS>(), [=](concurrency::tiled_index<TS, TS> t_lDX) restrict(amp)
        {
            //get global position for thread
            int in_Y = t_lDX.global[0];
            int in_X = t_lDX.global[1];

            Complex1 z;
            //make it relitve to raidius
            z = mapPoint(width, height, radius, in_X, in_Y);
            int ctr = 0;
            int iLoop = 0;
            while (iLoop <= n) {
                //our equation z = m^2 + c where c = imignary + real 
                z = c_add(c_mul(z, z), c);
                iLoop++;
                double iz = mod(z);

                //set coulours 
                if (iz > radius)
                {

                    
                   //out with SET colour accordingly 
                    ctr = ctr + 0xF;
                    imDAT[in_Y][in_X] = 0xCC00FF - ctr; //white

                }
                else {

                    //within = black
                    imDAT[in_Y][in_X] = 0x000000; //black

                }

            }
        });



    imDAT.synchronize();
}
void Julia::compute_JULIA_tile8(int width, int height, Complex1 c, double radius, int n) {
    //tile size 
    const int TS = 8;

    //copy image
    uint32_t* in_Image = &(image[0][0]);

    //create loacl varible for image data
    concurrency::array_view<uint32_t, 2> imDAT(HEIGHT, WIDTH, in_Image);

    //clear any data in it
    imDAT.discard_data();

    //start threads
    concurrency::parallel_for_each(imDAT.extent.tile<TS, TS>(), [=](concurrency::tiled_index<TS, TS> t_lDX) restrict(amp)
        {
            //get global position for thread
            int in_Y = t_lDX.global[0];
            int in_X = t_lDX.global[1];

            Complex1 z;
            //make it relitve to raidius
            z = mapPoint(width, height, radius, in_X, in_Y);
            int ctr = 0;
            int iLoop = 0;
            while (iLoop <= n) {
                //our equation z = m^2 + c where c = imignary + real 
                z = c_add(c_mul(z, z), c);
                iLoop++;
                double iz = mod(z);

                //set coulours 
                if (iz > radius)
                {


                    //out with SET colour accordingly 
                    ctr = ctr + 0xF;
                    imDAT[in_Y][in_X] = 0xCC00FF - ctr; //white

                }
                else {

                    //within = black
                    imDAT[in_Y][in_X] = 0x000000; //black

                }

            }
        });



    imDAT.synchronize();
}
void Julia::compute_JULIA_tile16(int width, int height, Complex1 c, double radius, int n) {
    //tile size 
    const int TS = 16;

    //copy image
    uint32_t* in_Image = &(image[0][0]);

    //create loacl varible for image data
    concurrency::array_view<uint32_t, 2> imDAT(HEIGHT, WIDTH, in_Image);

    //clear any data in it
    imDAT.discard_data();

    //start threads
    concurrency::parallel_for_each(imDAT.extent.tile<TS, TS>(), [=](concurrency::tiled_index<TS, TS> t_lDX) restrict(amp)
        {
            //get global position for thread
            int in_Y = t_lDX.global[0];
            int in_X = t_lDX.global[1];

            Complex1 z;
            //make it relitve to raidius
            z = mapPoint(width, height, radius, in_X, in_Y);
            int ctr = 0;
            int iLoop = 0;
            while (iLoop <= n) {
                //our equation z = m^2 + c where c = imignary + real 
                z = c_add(c_mul(z, z), c);
                iLoop++;
                double iz = mod(z);

                //set coulours 
                if (iz > radius)
                {


                    //out with SET colour accordingly 
                    ctr = ctr + 0xF;
                    imDAT[in_Y][in_X] = 0xCC00FF - ctr; //white

                }
                else {

                    //within = black
                    imDAT[in_Y][in_X] = 0x000000; //black

                }

            }
        });



    imDAT.synchronize();
}
void Julia::compute_JULIA_tile32(int width, int height, Complex1 c, double radius, int n) {
    //tile size 
    const int TS = 32;

    //copy image
    uint32_t* in_Image = &(image[0][0]);

    //create loacl varible for image data
    concurrency::array_view<uint32_t, 2> imDAT(HEIGHT, WIDTH, in_Image);

    //clear any data in it
    imDAT.discard_data();

    //start threads
    concurrency::parallel_for_each(imDAT.extent.tile<TS, TS>(), [=](concurrency::tiled_index<TS, TS> t_lDX) restrict(amp)
        {
            //get global position for thread
            int in_Y = t_lDX.global[0];
            int in_X = t_lDX.global[1];

            Complex1 z;
            //make it relitve to raidius
            z = mapPoint(width, height, radius, in_X, in_Y);
            int ctr = 0;
            int iLoop = 0;
            while (iLoop <= n) {
                //our equation z = m^2 + c where c = imignary + real 
                z = c_add(c_mul(z, z), c);
                iLoop++;
                double iz = mod(z);

                //set coulours 
                if (iz > radius)
                {


                    //out with SET colour accordingly 
                    ctr = ctr + 0xF;
                    imDAT[in_Y][in_X] = 0xCC00FF - ctr; //white

                }
                else {

                    //within = black
                    imDAT[in_Y][in_X] = 0x000000; //black

                }

            }
        });



    imDAT.synchronize();
}


void print_Values(long long int& time_taken4, long long int& time_taken8, long long int& time_taken16, long long int time_taken32, int& iCtr) {
    //if the file does not exist then create the file and append headder else just write times
    std::ifstream csvFileck("example.csv", std::ios_base::binary);
    if (!csvFileck.good()) {
        csvFileck.close();
        ofstream csvFile("example.csv", std::ios::app);
        csvFile << "All times are in (ms).\n";       
        csvFile << ",4 tile, 8 tile, 16 tile, 32 tile,\n";
        csvFile << "Run No, Time(ms), Time(ms), Time(ms), Time(ms)\n";
        csvFile.close();
    }
    else {
        csvFileck.close();
    }
    ofstream csvFile("example.csv", std::ios::app);
    csvFile << (iCtr) << (",") <<  (time_taken4) << (",") << (time_taken8) << "," << time_taken16 << "," << (time_taken32) << "\n";

    return;

}

Julia::Julia(){
   //use constructor to get varibles 
  //to be used in either Benchmark or OPENGL output

    std::cout << "////////////////////" << endl;
    std::cout << "//  Please enter  //" << endl;
    std::cout << "//imagnary number //" << endl;
    std::cout << "////////////////////" << endl;
    std::cin >> c.x;
    std::cout << "////////////////////" << endl;
    std::cout << "//  Please enter  //" << endl;
    std::cout << "//  Real number   //" << endl;
    std::cout << "////////////////////" << endl;
    std::cin >> c.y;
    std::cout << "////////////////////" << endl;
    std::cout << "//  Please enter  //" << endl;
    std::cout << "Number of Iterations" << endl;
    std::cout << "////////////////////" << endl;
    std::cin >> itr;
    std::cout << "////////////////////" << endl;
    std::cout << "//  Please enter  //" << endl;
    std::cout << "//     Radius    //" << endl;
    std::cout << "////////////////////" << endl;
    std::cin >> iR;
  
}

Julia::~Julia()
{
    // identfy where deconstuctor called
    cout << "Program Complete" << endl;
}


void Julia::Benchmark() {
   
    //Run every tile size 100 times. Each time outputing time taken to csv file
    //inclue writing out to file for integrity cheching


    //begin Performce evaluation
    int i = 0;
    for (i = 1; i < 101; i++) {


        //4 tile 
        the_clock::time_point start4 = the_clock::now();
        Julia::compute_JULIA_tile4(WIDTH, HEIGHT, c, iR, itr);
        the_clock::time_point end4 = the_clock::now();
        write_tga("res/textures/julia4.tga");

        //8 tile
        the_clock::time_point start8 = the_clock::now();
        Julia::compute_JULIA_tile8(WIDTH, HEIGHT, c, iR, itr);
        the_clock::time_point end8 = the_clock::now();
        write_tga("res/textures/julia8.tga");

        //16 tile 
        the_clock::time_point start16 = the_clock::now();
        Julia::compute_JULIA_tile16(WIDTH, HEIGHT, c, iR, itr);
        the_clock::time_point end16 = the_clock::now();
        write_tga("res/textures/julia16.tga");

        //32 tile
        the_clock::time_point start32 = the_clock::now();
        Julia::compute_JULIA_tile32(WIDTH, HEIGHT, c, iR, itr);
        the_clock::time_point end32 = the_clock::now();
        write_tga("res/textures/julia32.tga");
      
        //tile time 
        auto time_taken4 = duration_cast<milliseconds>(end4 - start4).count();
        auto time_taken8 = duration_cast<milliseconds>(end8 - start8).count();
        auto time_taken16 = duration_cast<milliseconds>(end16 - start16).count();
        auto time_taken32 = duration_cast<milliseconds>(end32 - start32).count();
       
        // print values
        print_Values( time_taken4, time_taken8, time_taken16, time_taken32, i);

    }
 }

void Julia::Ouput() {

    //from performance numbers 8+ tiles has dimishing results so 8 shall be used 
    compute_JULIA_tile8(WIDTH, HEIGHT, c, iR, itr);
    write_tga("./julia.tga");
  

   
}
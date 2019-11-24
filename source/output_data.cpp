// ---------------------------------------------------------------------
// GFractal Project
// Graham Harper
// ---------------------------------------------------------------------

#include "gfractal/include/output_data.h"

void OutputData::write_bitmap(NewtonFractal &frac, char* filename)
{
  int width = frac.image_dims[0];
  int height = frac.image_dims[1];
  int total_pixels = width*height;
  enum color { C_RED=1, C_GREEN=2, C_BLUE=3, C_BLACK=-1 };

  // SET UP THE RGB ARRAYS AND FILL THEM BASED ON THE SIMULATION
  int *r = new int[total_pixels];
  int *g = new int[total_pixels];
  int *b = new int[total_pixels];
  for(int i=0; i<total_pixels; ++i)
  {
    if(frac.root[i/width][i%width]==C_RED)
    {
      r[i] = 220;
      g[i] = 50;
      b[i] = 50;
    }
    else if(frac.root[i/width][i%width]==C_GREEN)
    {
      r[i] = 50;
      g[i] = 220;
      b[i] = 50;
    }
    else //if(frac.root[i/width][i%width]==C_BLUE)
    {
      r[i] = 50;
      g[i] = 50;
      b[i] = 220;
    }
    /*else //if(frac.root[i/width][i%width]==C_BLACK)
    {
      r[i] = 0;
      g[i] = 0;
      b[i] = 0;
    }*/

    // normally needs a check to make sure the rgb values don't fall out of the 0-255 range
    r[i] = r[i]*(1-((double)frac.its[i/width][i%width])/frac.max_its);
    g[i] = g[i]*(1-((double)frac.its[i/width][i%width])/frac.max_its);
    b[i] = b[i]*(1-((double)frac.its[i/width][i%width])/frac.max_its);
  }



  int arraysize = 3*total_pixels;   // number of RGB entries for the image
  int filesize = 54 + arraysize;    // file size in bytes (3bytes per pixel for 256bit)
  unsigned char *img = NULL;        // this will be the rgb pixel array
  img = (unsigned char *)malloc(arraysize);
  if(img == 0) {
    std::cout << "Unable to allocate image memory!" << std::endl; return;
  }


  // Write the rgb information linearly (bmp goes in bgr order for each group of 3 bytes)
  for(int i=0; i<total_pixels; ++i)
  {
    img[3*i] = b[i];
    img[3*i+1] = g[i];
    img[3*i+2] = r[i];
  }

  // Declare the file and open it
  FILE *fp;
  if(NULL==(fp=fopen(filename, "w"))) {
    std::cout << "Unable to open the file!" << std::endl; return;
  }

  // Define the header information
  unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
  unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};

  bmpfileheader[ 2] = (unsigned char)(filesize    ); // write the bytes in reverse order
  bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
  bmpfileheader[ 4] = (unsigned char)(filesize>>16);
  bmpfileheader[ 5] = (unsigned char)(filesize>>24);

  bmpinfoheader[ 4] = (unsigned char)(    width    );
  bmpinfoheader[ 5] = (unsigned char)(    width>> 8);
  bmpinfoheader[ 6] = (unsigned char)(    width>>16);
  bmpinfoheader[ 7] = (unsigned char)(    width>>24);
  bmpinfoheader[ 8] = (unsigned char)(   height    );
  bmpinfoheader[ 9] = (unsigned char)(   height>> 8);
  bmpinfoheader[10] = (unsigned char)(   height>>16);
  bmpinfoheader[11] = (unsigned char)(   height>>24);
  bmpinfoheader[20] = (unsigned char)(arraysize    );
  bmpinfoheader[21] = (unsigned char)(arraysize>>8 );
  bmpinfoheader[22] = (unsigned char)(arraysize>>16);
  bmpinfoheader[23] = (unsigned char)(arraysize>>24);


  // Output the header information together
  fwrite(bmpfileheader,1,14,fp);
  fwrite(bmpinfoheader,1,40,fp);
  // Write the pixel array data
  fwrite(img, 1, arraysize, fp);
  fclose(fp);

  free(img);
  // free(bmpfileheader); // not necessary right?
  // free(bmpinfoheader);

  std::cout << filename << " successfully exported" << std::endl;
  std::cout << "Image size   = " << width << "x" << height << std::endl;
  std::cout << "File size    = " << ((double)filesize)/1024.0/1024.0 << " MB" << std::endl;

  //return 0;
}

void OutputData::write_bitmap(JuliaFractal &frac, char* filename)
{
  int width = frac.image_dims[0];
  int height = frac.image_dims[1];
  int total_pixels = width*height;
  enum color { C_RED=1, C_GREEN=2, C_BLUE=3, C_BLACK=-1 };

  // SET UP THE RGB ARRAYS AND FILL THEM BASED ON THE SIMULATION
  int *r = new int[total_pixels];
  int *g = new int[total_pixels];
  int *b = new int[total_pixels];
  for(int i=0; i<total_pixels; ++i)
  {
    // normally needs a check to make sure the rgb values don't fall out of the 0-255 range
    r[i] = 255*(1-((double)frac.its[i/width][i%width])/frac.max_its);
    g[i] = 255*(1-((double)frac.its[i/width][i%width])/frac.max_its);
    b[i] = 255*(1-((double)frac.its[i/width][i%width])/frac.max_its);
  }


  int arraysize = 3*total_pixels;   // number of RGB entries for the image
  int filesize = 54 + arraysize;    // file size in bytes (3bytes per pixel for 256bit)
  unsigned char *img = NULL;        // this will be the rgb pixel array
  img = (unsigned char *)malloc(arraysize);
  if(img == 0) {
    std::cout << "Unable to allocate image memory!" << std::endl; return;
  }


  // Write the rgb information linearly (bmp goes in bgr order for each group of 3 bytes)
  for(int i=0; i<total_pixels; ++i)
  {
    img[3*i] = b[i];
    img[3*i+1] = g[i];
    img[3*i+2] = r[i];
  }

  // Declare the file and open it
  FILE *fp;
  if(NULL==(fp=fopen(filename, "w"))) {
    std::cout << "Unable to open the file!" << std::endl; return;
  }

  // Define the header information
  unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
  unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};

  bmpfileheader[ 2] = (unsigned char)(filesize    ); // write the bytes in reverse order
  bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
  bmpfileheader[ 4] = (unsigned char)(filesize>>16);
  bmpfileheader[ 5] = (unsigned char)(filesize>>24);

  bmpinfoheader[ 4] = (unsigned char)(    width    );
  bmpinfoheader[ 5] = (unsigned char)(    width>> 8);
  bmpinfoheader[ 6] = (unsigned char)(    width>>16);
  bmpinfoheader[ 7] = (unsigned char)(    width>>24);
  bmpinfoheader[ 8] = (unsigned char)(   height    );
  bmpinfoheader[ 9] = (unsigned char)(   height>> 8);
  bmpinfoheader[10] = (unsigned char)(   height>>16);
  bmpinfoheader[11] = (unsigned char)(   height>>24);
  bmpinfoheader[20] = (unsigned char)(arraysize    );
  bmpinfoheader[21] = (unsigned char)(arraysize>>8 );
  bmpinfoheader[22] = (unsigned char)(arraysize>>16);
  bmpinfoheader[23] = (unsigned char)(arraysize>>24);


  // Output the header information together
  fwrite(bmpfileheader,1,14,fp);
  fwrite(bmpinfoheader,1,40,fp);
  // Write the pixel array data
  fwrite(img, 1, arraysize, fp);
  fclose(fp);

  free(img);
  // free(bmpfileheader); // not necessary right?
  // free(bmpinfoheader);

  std::cout << filename << " successfully exported" << std::endl;
  std::cout << "Image size   = " << width << "x" << height << std::endl;
  std::cout << "File size    = " << ((double)filesize)/1024.0/1024.0 << " MB" << std::endl;

  //return 0;
}

//  This file contains sourcecode distributed as freeware. 
//  The intellectual property of the sourcecode is shown 
//  here to belong to Carlo Ciulla.

// Reference (book):

// [2] Carlo Ciulla "Signal Resilient to Interpolation: An Exploration on the 
// Approximation Properties of the Mathematical Functions" - CreateSpace Publisher - 
// June 2012; pp. 1 - 336, ISBN: 978-1477567487.

// Disclaimer:

// The website here named www.sourcecodewebsiteCarloCiulla.com 2013 [2] does not intend 
// to convey the meaning of profit making for what pertains to the content
// provided. --->>> Instead, when the content is downloaded, the user(s) are
// kindly invited to donate money to charity organizations involved in 
// helping people in need of food and water. <<<---


//  Project Title: Bivariate Cubic SRI Interpolation

#include < iostream >
#include < fstream >
#include < ostream.h >
#include < string >
#include < io.h >
#include < dos.h >
#include < conio.h >
#include < stdlib.h >
#include < sstream >
#include < stdio.h >
#include < iomanip >
#include < istream >
#include < math.h >

#define NSCALE 0.1	
#define ESCALE 0.1
#define TH 0

using namespace std;


class SRI2D2013 {

	int n1; // matrix size x
	int n2; // matrix size y

public:

	int getNofPixelsX(void) { return this->n1; };

	int getNofPixelsY(void) { return this->n2; };

	void setNofPixelsX(int x) { this->n1 = x; };

	void setNofPixelsY(int y) { this->n2 = y; };

public:

	struct data {

		double **OriginalSignal; // pointer to the matrix entry 

		double **Signal; // pointer to the matrix entry
		
		double **ClassicCurvature; // pointer to the matrix entry 
	
		double **ResilientCurvature; // pointer to the matrix entry 

		double ** ThePixICResilient; // pointer to the matrix entry 

		double **shifted_OriginalSignal; // pointer to the matrix entry 
	
		double **SE; // pointer to the matrix entry 

		double **ThePixICClassic; // pointer to the matrix entry 

		double **the_SRI_shifted_OriginalSignal; // pointer to the matrix entry

		double **HybridSignal; // pointer to the matrix entry

		double **SE_SRI; // pointer to the matrix entry 

		double **ResilientSignal;	// pointer to the matrix entry

		double **ICF; // pointer to the matrix entry

	}*pointer; // pointer to the matrices

public:

	SRI2D2013(int x, int y) : n1(x), n2(y) { };// constructor 
	
	void allocateData();

	~SRI2D2013() { } // destructor

};

void SRI2D2013::allocateData() { // allocate data


	 // (1) allocate struct 'data' (begin)
	 pointer = new data;
			
	 pointer->OriginalSignal = new double*[this->n1];

	 pointer->Signal = new double*[this->n1];

	 pointer->ClassicCurvature = new double*[this->n1];

	 pointer->ResilientCurvature = new double*[this->n1];

	 pointer->ThePixICResilient = new double*[this->n1];

	 pointer->shifted_OriginalSignal = new double*[this->n1];

	 pointer->SE = new double*[this->n1];

	 pointer->ThePixICClassic = new double*[this->n1];

	 pointer->the_SRI_shifted_OriginalSignal = new double*[this->n1];

	 pointer->HybridSignal = new double*[this->n1];

	 pointer->SE_SRI = new double*[this->n1];

	 pointer->ResilientSignal = new double*[this->n1];

	 pointer->ICF = new double*[this->n1];


	 for( int v=0; v < this->n1; v++ ) { // (1)
		 
		 pointer->OriginalSignal[v] = new double[this->n2];

		 pointer->Signal[v] = new double[this->n2];

		 pointer->ClassicCurvature[v] = new double[this->n2];

		 pointer->ResilientCurvature[v] = new double[this->n2];

		 pointer->ThePixICResilient[v] = new double[this->n2];

		 pointer->shifted_OriginalSignal[v] = new double[this->n2];

		 pointer->SE[v] = new double[this->n2];

		 pointer->ThePixICClassic[v] = new double[this->n2];

		 pointer->the_SRI_shifted_OriginalSignal[v] = new double[this->n2];

  	     pointer->HybridSignal[v] = new double[this->n2];

		 pointer->SE_SRI[v] = new double[this->n2];

		 pointer->ResilientSignal[v] = new double[this->n2];

		 pointer->ICF[v] = new double[this->n2];


	  } // (1) allocate struct 'data' (end)


		// (2) initialize (begin)
		for( v=0; v < this->n1; v++ ) { // (a)

			for( int f=0; f < this->n2 ; f++ ) { // (b)
		 
			pointer->OriginalSignal[v][f] = (double)0.0;

			pointer->Signal[v][f] = (double)0.0;

			pointer->ClassicCurvature[v][f] = (double)0.0;

			pointer->ResilientCurvature[v][f] = (double)0.0;

			pointer->ThePixICResilient[v][f] = (double)0.0;

			pointer->shifted_OriginalSignal[v][f] = (double)0.0;

			pointer->SE[v][f] = (double)0.0;

			pointer->ThePixICClassic[v][f] = (double)0.0;

			pointer->the_SRI_shifted_OriginalSignal[v][f] = (double)0.0;

			pointer->HybridSignal[v][f] = (double)0.0;

			pointer->SE_SRI[v][f] = (double)0.0;

			pointer->ResilientSignal[v][f] = (double)0.0;

			pointer->ICF[v][f] = (double)0.0;

			 } //(b)

		 } //(a)
		// (2) initialize (end)

} // allocate data


int main ( int argc, char * argv[] ) {

	char outputFile[128]="SRI2D.log";

	FILE * savedata;

	double MAX = 5000000000000000000.0;

if (argc < 8)  { std::cout << endl;
				 std::cout << "Please type the image file name" << endl;
				 std::cout << "Please make sure that the image format is Analyze 'double': 64 bits real" << endl;
				 std::cout << "Before running the program, please make sure that the image is padded of 'n >= 0'";
				 std::cout << "number of pixels along X and Y" << endl;
				 std::cout << "Please enter the number of pixels along the X direction (integer)" << endl;
				 std::cout << "Please enter the number of pixels along the Y direction (integer)" << endl;
				 std::cout << "Please enter the pixel size along the X direction (double)" << endl;
				 std::cout << "Please enter the pixel size along the Y direction (double)" << endl;
				 std::cout << "Please enter that 'n >= 0' number of pixels along X, Y and Z which will pad the image" << endl;
				 std::cout << "Some data will be lost if you enter a value of n which is greater than" << endl;
				 std::cout << "the actual number of pixels along X and Y which was used to pad the image" << endl;
				 std::cout << "before running the program." << endl;
				 std::cout << "Please type 'n' to scale the Image Data or 'e' to exponentialize the Image Data" << endl;
				 std::cout << endl;
				 exit(0); }

else { // run the program (begin)

	
	if ((savedata = fopen(outputFile,"w"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // processing (begin)

	int n1 = atoi(argv[2]);
	int n2 = atoi(argv[3]);

	double XPixelSize = atof(argv[4]);
	double YPixelSize = atof(argv[5]);

	char imageFileName[128];

	int PAD = atoi(argv[6]);

	unsigned char Fyn = 'n';

	Fyn = *argv[7];

	if ( PAD < 0 ) { // if test PAD
	
		std::cout << "Please make sure to pad the image with 'n >= 0' number of pixels along X, Y and Z" << endl;
	
		fprintf(savedata,"%s\n", "Please make sure to pad the image with 'n >= 0' number of pixels along X, Y and Z");

		fclose(savedata);
	
		exit(0);
	
	} // if test PAD

	sprintf(imageFileName, "%s", argv[1]);

	std::cout << endl;
	std::cout << "The image file name is: " << imageFileName << endl;
	std::cout << "The number of pixels along the X direction is: " << atoi(argv[2]) << endl;
	std::cout << "The number of pixels along the Y direction is: " << atoi(argv[3]) << endl;
	std::cout << "The pixel size along the X direction is: " << atof(argv[4]) << endl;
	std::cout << "The pixel size along the Y direction is: " << atof(argv[5]) << endl;
	std::cout << "The 'n' number of pixels along X and Y which you entered to pad the image is: " << atoi(argv[6]) << endl;
	std::cout << "Some data will be lost if you enter a value of n which is greater than" << endl;
	std::cout << "the actual number of pixels along X and Y which was used to pad the image" << endl;
	std::cout << "before running the program." << endl;

	if ( tolower(Fyn) == 'e' )
	std::cout << "The program exponentialize the Image Data before processing: " << Fyn << endl;
	else if ( tolower(Fyn) == 'n' ) 
	std::cout << "The program scales the Image Data before processing: " << Fyn << endl;
	std::cout << endl;

	fprintf(savedata,"%s%s\n", "The image file name is: " , imageFileName);
	fprintf(savedata,"%s%d\n", "The number of pixels along the X direction is: ", n1);
	fprintf(savedata,"%s%d\n", "The number of pixels along the Y direction is: ", n2);
	fprintf(savedata,"%s%lf\n", "The pixel size along the X direction is: ", XPixelSize);
	fprintf(savedata,"%s%lf\n", "The pixel size along the Y direction is: ", YPixelSize);
	fprintf(savedata,"%s%d\n", "The 'n' number of pixels along X and Y which you entered to pad the image is: ", PAD);
	fprintf(savedata,"%s\n", "Some data will be lost if you enter a value of n which is greater than");
	fprintf(savedata,"%s\n", "the actual number of pixels along X and Y which was used to pad the image");
	fprintf(savedata,"%s\n", "before running the program.");

	if ( tolower(Fyn) == 'e' )
	fprintf(savedata,"%s%c\n", "The program exponentialize the Image Data before processing: ", Fyn);
	else if ( tolower(Fyn) == 'n' )
	fprintf(savedata,"%s%c\n", "The program scales the Image Data before processing: ", Fyn);
	fprintf(savedata,"\n");


	SRI2D2013 SRI(n1,n2);

	SRI.allocateData();

	/// read image file (begin)
	FILE * pf;

	if ((pf = fopen(imageFileName,"rb+"))==NULL)
	{

		std::cout << "Cannot open file: " << imageFileName << endl;
		fprintf(savedata,"%s%s\n", "Cannot open file: " , imageFileName );
		exit(0);

	} else { // else

	double number;

	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim
			
		fread(&number,sizeof(double),1,pf);
		
		SRI.pointer->OriginalSignal[i1][i2] = (double)number;

		SRI.pointer->Signal[i1][i2] = (double)number;
                          
		} // y dim
        
	}  // x dim 

      	
    fclose (pf);


	} // else 
	/// read image file (end)

	std::cout << "Image data loaded" << endl;
	
	double max=-MAX;
	double min=MAX;

	// make decision as to if standarzize or scale the Image data (begin)
	if ( tolower(Fyn) == 'e' ) {
		
	double Std = 0, Average = 0;
	long int counting = 0;
	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

			if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) {

			Average += (double) SRI.pointer->OriginalSignal[i1][i2];

			counting++;

			}
			
		} // y dim
        
	}  // x dim 

	Average /= ((double)counting);

	counting = 0;

	for (i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

			if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) {

			Std = (double)Std + ((double) (Average - SRI.pointer->OriginalSignal[i1][i2]) * 
				                          (Average - SRI.pointer->OriginalSignal[i1][i2]) );

			counting++;

			}

		} // y dim
        
	}  // x dim 

	Std = (double) sqrt( (double) Std / ((double)counting) );


	// standardize (begin)
	for (i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

		   if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) { 

           SRI.pointer->Signal[i1][i2] = (double) ESCALE * ( (double) exp((double) (SRI.pointer->OriginalSignal[i1][i2] - Average) / Std) );
       
		   } else if ( (double)SRI.pointer->OriginalSignal[i1][i2] <= TH ) {
  	
			   SRI.pointer->Signal[i1][i2] = (double)0.0;
			
		   }

		} // y dim
        
	}  // x dim 
	// standardize (end)

	} else if ( tolower(Fyn) == 'n' )
	{ // make decision as to if standarzize or scale the Image data 

	/// compute max and min of data (begin)
	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim
	
		if( SRI.pointer->OriginalSignal[i1][i2] > (double)max ) 
			
			max = (double)SRI.pointer->OriginalSignal[i1][i2];
              
		if( SRI.pointer->OriginalSignal[i1][i2] < (double)min ) 
			
			min = (double)SRI.pointer->OriginalSignal[i1][i2];
		

		} // y dim
        
	}  // x dim
	/// compute max and min of data (end)

	// scale (begin)
	for (i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

		   if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) { 

           if ( max == min ) SRI.pointer->Signal[i1][i2] = (double)0.0;

           else SRI.pointer->Signal[i1][i2] = (double) NSCALE * (min - SRI.pointer->OriginalSignal[i1][i2]) / (min - max) ;
       
		   } else if ( (double)SRI.pointer->OriginalSignal[i1][i2] <= TH ) {
  	
			   SRI.pointer->Signal[i1][i2] = (double)0.0;
			
		   }

		} // y dim
        
	}  // x dim 
	
	// scale (end)
	std::cout << "Image data scaled" << endl;
	} // make decision as to if standarzize or scale the Image data (end)

	/// run JAVA (begin)
	char command[200];
	sprintf(command, "%s%s%s%d%s%d%s%c%s%s%s%s", "java -jar Convolutions2013.jar ", 
		                                         imageFileName, " ", n1, " ", n2, " ", 
												 Fyn, " ", "alpha3.img", " ", "alpha2.img"); 
	system(command);
	/// run JAVA (end)

	
	/// allocate memory & store ALPHAs (begin)
	double * ALPHA3 = 0;
	double * ALPHA2 = 0;

	/// allocate ALPHAs (begin)
	if ((ALPHA3 = (double *) calloc( n1*n2, sizeof(double)) ) == NULL)
	{

	std::cout << "Not enough memory to allocate Image data, Exit." << endl;
    fprintf(savedata,"%s\n", "Not enough memory to allocate Image data, Exit.");

	fclose(savedata);
	
	SRI.~SRI2D2013();
	exit(0);

	} else { // else

	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

		int index = ((int) i2*n1 + i1); 

		*(ALPHA3 + index) = (double)0.0;
    	

		} // y dim
        
	}  // x dim 

	}//else

	if ((ALPHA2 = (double *) calloc( n1*n2, sizeof(double)) ) == NULL)
	{

	std::cout << "Not enough memory to allocate Image data, Exit." << endl;
    fprintf(savedata,"%s\n", "Not enough memory to allocate Image data, Exit.");

	fclose(savedata);
	
	free(ALPHA3);
	SRI.~SRI2D2013();
	exit(0);

	} else { // else


	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim
		
		int index = ((int) i2*n1 + i1); 

		*(ALPHA2 + index) = (double)0.0;


		} // y dim
        
	}  // x dim 

	}//else
	/// allocate ALPHAs (end)

	/// read alpha (begin)
	FILE * readAlpha;
	char inputFile[128];
	double readdata;
	
	sprintf(inputFile, "%s","alpha3.img");

	if ((readAlpha = fopen(inputFile,"rb"))==NULL)
	{

		std::cout << "Cannot open input file, Now Exit..." << endl;
		fprintf(savedata,"%s\n", "Cannot open input file, Now Exit...");

		free(ALPHA3);
		free(ALPHA2);
		SRI.~SRI2D2013();
		exit(0);
		
	} else  { // (read)


	for( int i1=0; i1 < n1; i1++ ) { // (a)

		for( int i2=0; i2 < n2; i2++ ) {
	
		int index = ((int) i2*n1 + i1); 

		fread(&readdata, sizeof(double),1, readAlpha);

		*(ALPHA3 + index) = (double)readdata;

		}

	} // (a)

	fclose(readAlpha);

	} // (read)

	sprintf(inputFile, "%s","alpha2.img");

	if ((readAlpha = fopen(inputFile,"rb"))==NULL)
	{

		std::cout << "Cannot open input file, Now Exit..." << endl;
		fprintf(savedata,"%s\n", "Cannot open input file, Now Exit...");

		free(ALPHA3);
		free(ALPHA2);
		SRI.~SRI2D2013();
		exit(0);

	} else  { // (read)


	for( int i1=0; i1 < n1; i1++ ) { // (a)

		for( int i2=0; i2 < n2; i2++ ) {
	
		int index = ((int) i2*n1 + i1); 

		fread(&readdata, sizeof(double),1, readAlpha);

		*(ALPHA2 + index) = (double)readdata;

		}

	} // (a)

	fclose(readAlpha);

	} // (read)
	/// read alpha (end)
	/// allocate memory & store ALPHAs (end)

	std::cout << "Image data scaled" << endl;

	fprintf(savedata, "%s\t %s\t %s\t\t %s\t\t %s\n", "misplacement_X", "misplacement_Y", "SE", "SRI_SE", "SE Difference"); 
	fprintf(savedata,"\n");
	std::cout << "Now Computing..." << endl; 

	double STEP_A = (double)0.0;
	double STEP_MX = (double)0.0;
	double STEP_MY = (double)0.0;

	double x_misplacement_X = (double)0.001;
	double y_misplacement_Y = (double)0.001;
	double theta = (double)0.0001;


	 //---> major for loop (begin) <---//
	for (int step = 1; step < 100; step++) {

	double misplacement_X = ((double)1.0 - ( cos( (double)theta + STEP_A) + sin( (double)theta + STEP_A) ) + (double)x_misplacement_X + (double)STEP_MX);
    double misplacement_Y = ((double)1.0 - (-sin( (double)theta + STEP_A) + cos( (double)theta + STEP_A) ) + (double)y_misplacement_Y + (double)STEP_MY);

	misplacement_X = ((double)misplacement_X/XPixelSize);
    misplacement_Y = ((double)misplacement_Y/YPixelSize);

	   //////////////////***********/////////////////////
	  // Above formula scales the misplacement to the  //
	  // pixel size the same way the following formula //
	  // would do: (min - misplacement)/(min - max)    //  
	  //////////////////***********//////////////////////

    // shift the image of the given misplacement (begin)
	// calculate curvature of model interpolation function (begin)
	double alpha3, alpha2;
	double a, b, c, d, e, f, g;
	double H4_2D_1, H4_2D_2;
	double TheShift;
	
	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

		if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) { 


		int index = ((int) i2*n1 + i1); 

		alpha3 =  (double)*(ALPHA3 + index);

		alpha2 =  (double)*(ALPHA2 + index);

		// compute polynomial coefficients (begin)
		a = ((double) 0.5 * (misplacement_X + misplacement_Y) * 
			                (misplacement_X + misplacement_Y) * 
							(misplacement_X + misplacement_Y) );

		b = - ((double) (misplacement_X + misplacement_Y) * (misplacement_X + misplacement_Y));

		c = ((double)2.0/3.0);

		d = - ((double) (1.0/6.0) * (misplacement_X + misplacement_Y) * 
			                        (misplacement_X + misplacement_Y) * 
									(misplacement_X + misplacement_Y));

		e = ((double) (misplacement_X + misplacement_Y) * 
			          (misplacement_X + misplacement_Y));

		f = -((double) 2.0 * (misplacement_X + misplacement_Y));

		g = ((double)4.0/3.0);
		// compute polynomial coefficients (end)

		// compute the h functions without transfer function (begin) 
		H4_2D_1 =  ((double) ( ( a + b + c ) * alpha3 ) ) ;

		H4_2D_2 =  ((double) ( ( d + e + f + g ) * alpha2 ) );
		// compute the h functions without transfer function (end) 

		SRI.pointer->shifted_OriginalSignal[i1][i2] = 
			
		(double)SRI.pointer->OriginalSignal[i1][i2] + ((double)H4_2D_1 + (double)H4_2D_2);
		
		
		TheShift = (double)sqrt( ((double)misplacement_X * misplacement_X) + 
			                     ((double)misplacement_Y * misplacement_Y) );

		// calculate curvature of model interpolation function (Classic)
		SRI.pointer->ClassicCurvature[i1][i2] = 
		
		((double)4.0 * ( alpha3 * ( 3.0 * (misplacement_X + misplacement_Y) - 2.0 ) + 
		                 alpha2 * ( -(misplacement_X + misplacement_Y) + 2.0 ) ) );

		} else if ( (double)SRI.pointer->OriginalSignal[i1][i2] <= TH ) { }

		} // y dim
        
	}  // x dim
	
	std::cout << "Image shifted of the given misplacement" << endl;
	std::cout << "Curvature of model interpolation function calculated" << endl;
	// shift the image of the given misplacement (end)
	// calculate curvature of model interpolation function (end)



	// calculate the signal resilient to interpolation (begin)
	double a1, a2, a3, a4, a5;
	double b1, b2, b3, b4, b5, b6, b7, b8;
	double c1, c2, c3, c4;
	double d1, d2, d3;
	double e1, e2, f1;
	double GAMMA, g1, g2, g3, DEN;
	double lambda;
	double tau1, tau2, tau3;
	double derRXX, RYY, sodeRXY;
	double mu1, mu2, mu3;
	double psi1, psi2, psi3, psi4;
	double secondRYX, deLambdaX;
	double ch1, ch2, ch3, ch4;
	double hrc1, hrc2, hrc3, hrc4;
	double de2LambdaY, de2inzero;
	double etasixdex, deyetasix;
	double XXdex2etasix, YYdey2etasix;
	double XYdexy2etasix, YXdeyx2etasix;
	double capFIeta6, CurvRf, Add2, Add3, Add4;


	for (i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

		if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) { 

		
		int index = ((int) i2*n1 + i1); 

		alpha3 =  (double)*(ALPHA3 + index);

		alpha2 =  (double)*(ALPHA2 + index);	


		a1 = ((double) (3.0/2.0) * alpha3 * alpha3 - 
			           (1.0/2.0) * alpha3 * alpha2 - 
					   (3.0/6.0) * alpha3 * alpha2 + 
					   (1.0/6.0) * alpha2 * alpha2 );


		b1 = ((double) pow(misplacement_X, 5.0) * misplacement_Y / 5.0 );

		b2 = ((double) (3.0/8.0) * pow(misplacement_X, 4.0) * pow(misplacement_Y, 2.0) ); 

		b3 = ((double) pow(misplacement_X, 3.0) * pow(misplacement_Y, 3.0) / 3.0 );

		b4 = ((double) pow(misplacement_X, 2.0) * pow(misplacement_Y, 4.0) / 8.0 );

		b5 = ((double) pow(misplacement_X, 4.0) * pow(misplacement_Y, 2.0) / 8.0 ); 

		b6 = ((double) pow(misplacement_X, 3.0) * pow(misplacement_Y, 3.0) / 3.0 );

		b7 = ((double) (3.0/8.0) * pow(misplacement_X, 2.0) * pow(misplacement_Y, 4.0));

		b8 = ((double) misplacement_X * pow(misplacement_Y, 5.0) / 5.0 );


		a2 = ((double) -4.0 * alpha3 * alpha3 + 
			            2.0 * alpha3 * alpha2 + 
				  (4.0/3.0) * alpha3 * alpha2 - 
				  (4.0/3.0) * alpha2 * alpha2 );


		c1 = ((double) pow(misplacement_X, 4.0) * misplacement_Y / 4.0 );

		c2 = ((double) pow(misplacement_X, 3.0) * pow(misplacement_Y, 2.0) / 2.0);

		c3 = ((double) pow(misplacement_X, 2.0) * pow(misplacement_Y, 3.0) / 2.0);

		c4 = ((double) misplacement_X * pow(misplacement_Y, 4.0) / 4.0); 

		 
		a3 = ((double) 2.0 * alpha3 * alpha3 - 
			           2.0 * alpha3 * alpha2 - 
					   8.0 * alpha3 * alpha2 + 
					   4.0 * alpha2 * alpha2); 


		d1 = ((double) pow(misplacement_X, 3.0) * misplacement_Y / 3.0);

		d2 = ((double) pow(misplacement_X, 2.0) * pow(misplacement_Y, 2.0) / 2.0);

		d3 = ((double) misplacement_X * pow(misplacement_Y, 3.0) / 3.0);

		a4 = ((double) 2.0 * alpha3 * alpha3 - 
			     (2.0/3.0) * alpha3 * alpha2 + 
				       8.0 * alpha3 * alpha2 - 
				(16.0/3.0) * alpha2 * alpha2); 


		e1 = ((double) pow(misplacement_X, 2.0) * misplacement_Y / 2.0);

		e2 = ((double) misplacement_X * pow(misplacement_Y, 2.0) / 2.0);


		a5 = ((double) -(4.0/3.0) * alpha3 * alpha3 + 
			            (4.0/3.0) * alpha3 * alpha2 - 
						(8.0/3.0) * alpha3 * alpha2 + 
						(8.0/3.0) * alpha2 * alpha2); 

		f1 = ((double)misplacement_X * misplacement_Y);


		GAMMA = ((double) a1 * ( b1 + b2 + b3 + b4 + b5 + b6 + b7 + b8 )); 

		GAMMA = (double)GAMMA + ((double)a2 * ( c1 + c2 + c3 + c4 )); 

		GAMMA = (double)GAMMA + ((double)a3 * ( d1 + d2 + d3 ));

		GAMMA = (double)GAMMA + ((double)a4 * ( e1 + e2 )); 

		GAMMA = (double)GAMMA + ((double)a5 * f1); 

		GAMMA = ((double)4.0 * GAMMA); 


		g1 = ((double) 4.0 * misplacement_X * misplacement_Y * ( -2.0 * alpha3 + 2.0 * alpha2 ));

		g2 = ((double) - 4.0 * alpha3 *  ( 3.0 * ( (pow(misplacement_X, 2.0) * misplacement_Y / 2.0) + 
			                                       (misplacement_X * pow(misplacement_Y, 2.0) / 2.0) ) - 
			                                       (2.0 * misplacement_X * misplacement_Y)  ) );

		g3 = ((double) - 4.0 * alpha2 * ( -( (pow(misplacement_X, 2.0) * misplacement_Y / 2.0) + 
			                                 (misplacement_X * pow(misplacement_Y, 2.0) / 2.0) ) + 
											 (2.0 * misplacement_X * misplacement_Y)  ) );

		DEN = ((double) g1 + g2 + g3 );


		if ( ((double)DEN) != 0.0 )
			 SRI.pointer->ResilientSignal[i1][i2] = ((double)GAMMA / DEN);
		else SRI.pointer->ResilientSignal[i1][i2] = (double)SRI.pointer->OriginalSignal[i1][i2];
		// calculate the signal resilient to interpolation (end)


		// calculate the curvature of the Resilient Signal (begin) 
		
		// this line changes GAMMA into lambda (lambda = GAMMA / 4.0)
		lambda = ((double)GAMMA / 4.0);

		// 2011
		// calculation of the coefficients of the total curvature
		// Eq. 82

		tau1 = ((double)4.0 * pow(misplacement_X, 3.0) * misplacement_Y );

		tau1 = (double)tau1 + ((double) (36.0/8.0) * pow(misplacement_X, 2.0) * pow(misplacement_Y, 2.0) );

		tau1 = (double)tau1 + ((double) 2.0 * misplacement_X * pow(misplacement_Y, 3.0) ); 

		tau1 = (double)tau1 + ((double) pow(misplacement_Y, 4.0) / 4.0 );

		tau1 = (double)tau1 + ((double) (3.0/2.0) * pow(misplacement_X, 2.0) * pow(misplacement_Y, 2.0) );

		tau1 = (double)tau1 + ((double) 2.0 * misplacement_X * pow(misplacement_Y, 3.0) ); 

		tau1 = (double)tau1 + ((double) (6.0/8.0) * pow(misplacement_Y, 4.0) );

		
		derRXX = ((double)a1 * tau1); 


		tau2 = ((double) 3.0 * pow(misplacement_X, 2.0) * misplacement_Y );

		tau2 = (double)tau2 + ((double) 3.0 * misplacement_X * pow(misplacement_Y, 2.0) );

		tau2 = (double)tau2 + ((double) pow(misplacement_Y, 3.0) );


		derRXX = (double)derRXX + ((double)a2 * tau2);


		tau3 = ((double) 2.0 * misplacement_X * misplacement_Y );

		tau3 = (double)tau3 + (double)pow(misplacement_Y, 2.0);
       

		derRXX = (double)derRXX + ((double)a3 * tau3);

		derRXX = (double)derRXX + ((double)a4 * misplacement_Y); 


		// Eq. 83
		mu1 = ((double) ( (6.0/8.0) * pow(misplacement_X, 4.0) ) + ( 2.0 * pow(misplacement_X, 3.0) * misplacement_Y ));

		mu1 = (double)mu1 + ((double) (3.0/2.0) * pow(misplacement_X, 2.0) * pow(misplacement_Y, 2.0)); 

		mu1 = (double)mu1 + ((double) pow(misplacement_X, 4.0) / 4.0);

		mu1 = (double)mu1 + ((double) 2.0 * pow(misplacement_X, 3.0) * misplacement_Y);

		mu1 = (double)mu1 + ((double) (36.0/8.0) * pow(misplacement_X, 2.0) * pow(misplacement_Y, 2.0));

		mu1 = (double)mu1 + ((double) 4.0 * misplacement_X * pow(misplacement_Y, 3.0));


		RYY = ((double)a1 * mu1);


		mu2 = ((double) pow(misplacement_X, 3.0) + ( 3.0 * pow(misplacement_X, 2.0) * misplacement_Y ));

		mu2 = (double)mu2 + ((double) 3.0 * misplacement_X * pow(misplacement_Y, 2.0) );
     

		RYY = (double)RYY + ((double)a2 * mu2);


		mu3 = ((double) pow(misplacement_X, 2.0) + ( 2.0 * misplacement_X * misplacement_Y ));


		RYY = (double)RYY + ((double)a3 * mu3);


		RYY = (double)RYY + ((double)a4 * misplacement_X); 


		// Eq. 84
		psi1 = ((double) pow(misplacement_X, 4.0) + ( (24.0/8.0) * pow(misplacement_X, 3.0) * misplacement_Y )); 

		psi1 = (double)psi1 + ((double) 3.0 * pow(misplacement_X, 2.0) * pow(misplacement_Y, 2.0) );

		psi1 = (double)psi1 + ((double) misplacement_X * pow(misplacement_Y, 3.0) );

		psi1 = (double)psi1 + ((double) pow(misplacement_X, 3.0) * misplacement_Y );

		psi1 = (double)psi1 + ((double) 3.0 * pow(misplacement_X, 2.0) * pow(misplacement_Y, 2.0) );

		psi1 = (double)psi1 + ((double) (24.0/8.0) * misplacement_X * pow(misplacement_Y, 3.0) );

		psi1 = (double)psi1 + ((double) pow(misplacement_Y, 4.0) );


		sodeRXY = ((double)a1 * psi1);


		psi2 = ((double)pow(misplacement_X, 3.0) + ( 3.0 * pow(misplacement_X, 2.0) * misplacement_Y ));

		psi2 = (double)psi2 + ((double) 3.0 * misplacement_X * pow(misplacement_Y, 2.0) );

		psi2 = (double)psi2 + ((double) pow(misplacement_Y, 3.0));


		sodeRXY = (double)sodeRXY + ((double)a2 * psi2);


		psi3 = ((double) pow(misplacement_X, 2.0) + ( 2.0 * misplacement_X * misplacement_Y ) + pow(misplacement_Y, 2.0));


		sodeRXY = (double)sodeRXY + ((double)a3 * psi3);


		psi4 = ((double)misplacement_X + misplacement_Y);


		sodeRXY = (double)sodeRXY + ((double)a4 * psi4) + (double)a5;


		secondRYX = (double)sodeRXY; // Eq. (85)

		// Eq. 80
		ch1 = ((double)pow(misplacement_X, 4.0) * misplacement_Y);

		ch1 = (double)ch1 + ((double) (12.0/8.0) * pow(misplacement_X, 3.0) * pow(misplacement_Y, 2.0) );

		ch1 = (double)ch1 + ((double) pow(misplacement_X, 2.0) * pow(misplacement_Y, 3.0) );

		ch1 = (double)ch1 + ((double) misplacement_X * pow(misplacement_Y, 4.0) / 4.0);

		ch1 = (double)ch1 + ((double) pow(misplacement_X, 3.0) * pow(misplacement_Y, 2.0) / 2.0);

		ch1 = (double)ch1 + ((double) pow(misplacement_X, 2.0) * pow(misplacement_Y, 3.0));

		ch1 = (double)ch1 + ((double) (6.0/8.0) * misplacement_X * pow(misplacement_Y, 4.0));

		ch1 = (double)ch1 + ((double) pow(misplacement_Y, 5.0) / 5.0);


		deLambdaX = ((double)a1 * ch1);


		ch2 = ((double) pow(misplacement_X, 3.0) * misplacement_Y);

		ch2 = (double)ch2 + ((double) (3.0/2.0) * pow(misplacement_X, 2.0) * pow(misplacement_Y, 2.0));

		ch2 = (double)ch2 + ((double) misplacement_X * pow(misplacement_Y, 3.0));

		ch2 = (double)ch2 + ((double) pow(misplacement_Y, 4.0) / 4.0);


		deLambdaX = (double)deLambdaX + ((double)a2 * ch2);


		ch3 = ((double) pow(misplacement_X, 2.0) * misplacement_Y);

		ch3 = (double)ch3 + ((double) misplacement_X * pow(misplacement_Y, 2.0));

		ch3 = (double)ch3 + ((double) pow(misplacement_Y, 3.0) / 3.0);


		deLambdaX = (double)deLambdaX + ((double)a3 * ch3);


		ch4 = ((double)misplacement_X * misplacement_Y) + ((double) pow(misplacement_Y, 2.0) / 2.0);


		deLambdaX = (double)deLambdaX + ((double)a4 * ch4);


		deLambdaX = (double)deLambdaX + ((double)a5 * misplacement_Y);


		// Eq. 81
		hrc1 = ((double) pow(misplacement_X, 5.0) / 5.0 );

		hrc1 = (double)hrc1 + ((double) (6.0/8.0) * pow(misplacement_X, 4.0) * misplacement_Y);

		hrc1 = (double)hrc1 + ((double) pow(misplacement_X, 3.0) * pow(misplacement_Y, 2.0));

		hrc1 = (double)hrc1 + ((double) pow(misplacement_X, 2.0) * pow(misplacement_Y, 3.0) / 2.0);

		hrc1 = (double)hrc1 + ((double) pow(misplacement_X, 4.0) * misplacement_Y / 4.0);

		hrc1 = (double)hrc1 + ((double) pow(misplacement_X, 3.0) * pow(misplacement_Y, 2.0));

		hrc1 = (double)hrc1 + ((double) (12.0/8.0) * pow(misplacement_X, 2.0) * pow(misplacement_Y, 3.0));

		hrc1 = (double)hrc1 + ((double) misplacement_X * pow(misplacement_Y, 4.0));


		de2LambdaY = ((double)a1 * hrc1);


		hrc2 = ((double) pow(misplacement_X, 4.0) / 4.0);

		hrc2 = (double)hrc2 + ((double) pow(misplacement_X, 3.0) * misplacement_Y);

		hrc2 = (double)hrc2 + ((double) (3.0/2.0) * pow(misplacement_X, 2.0) * pow(misplacement_Y, 2.0));

		hrc2 = (double)hrc2 + ((double) misplacement_X * pow(misplacement_Y, 3.0));


		de2LambdaY = (double)de2LambdaY + ((double)a2 * hrc2);


		hrc3 = ((double) pow(misplacement_X, 3.0) / 3.0);

		hrc3 = (double)hrc3 + ((double) pow(misplacement_X, 2.0) * misplacement_Y);

		hrc3 = (double)hrc3 + ((double) misplacement_X * pow(misplacement_Y, 2.0));


		de2LambdaY = (double)de2LambdaY + ((double)a3 * hrc3);


		hrc4 = ((double) pow(misplacement_X, 2.0) / 2.0);

		hrc4 = (double)hrc4 + ((double) misplacement_X * misplacement_Y);


		de2LambdaY = (double)de2LambdaY + ((double)a4 * hrc4);

		de2LambdaY = (double)de2LambdaY + ((double)a5 * misplacement_X); 


		de2inzero = ((double) (- 2.0 * alpha3) + (2.0 * alpha2));


		// Eq. 74
		etasixdex = ((double) 4.0 * misplacement_Y * de2inzero); 

		etasixdex = (double)etasixdex - ((double) ( 4.0 * alpha3 ) * 
		( 3.0 * ( ( misplacement_X * misplacement_Y ) + ( pow(misplacement_Y, 2.0) / 2.0 ) ) - ( 2.0 * misplacement_Y ) ) );

		etasixdex = (double)etasixdex - ((double) ( 4.0 * alpha2 ) * 
		( - ( ( misplacement_X * misplacement_Y ) + ( pow(misplacement_Y, 2.0) / 2.0 ) ) + ( 2.0 * misplacement_Y ) ) );


		// Eq. 75
		deyetasix = ((double) 4.0 * misplacement_X * de2inzero); 

		deyetasix = (double)deyetasix - ((double) ( 4.0 * alpha3 ) * 
		( 3.0 * ( ( misplacement_X * misplacement_X / 2.0 ) + ( misplacement_X * misplacement_Y ) ) - ( 2.0 * misplacement_X ) ) );

		deyetasix = (double)deyetasix - ((double) ( 4.0 * alpha2 ) * 
		( - ( ( misplacement_X * misplacement_X / 2.0 ) + ( misplacement_X * misplacement_Y ) ) + ( 2.0 * misplacement_X ) ) );


		// Eq. 76
		XXdex2etasix = ((double) ( - 4.0 * alpha3 * 3.0 * misplacement_Y ) + ( 4.0 * alpha2 * misplacement_Y ));

		// Eq. 77
		YYdey2etasix = ((double) ( - 4.0 * alpha3 * 3.0 * misplacement_X ) + ( 4.0 * alpha2 * misplacement_X ));


		// Eq. 78
		XYdexy2etasix = ((double) ( 4.0 * de2inzero ) - ( 4.0 * alpha3 * ( 3.0 * ( misplacement_X + misplacement_Y ) - 2.0 ) ) ); 

		XYdexy2etasix = (double)XYdexy2etasix - ((double) 4.0 * alpha2 * ( - ( misplacement_X + misplacement_Y ) + 2.0 ) ); 

		// Eq. 79
		YXdeyx2etasix = (double)XYdexy2etasix;


		// calculation of the coefficients of the total curvature (begin)

		//calculation of eta6 (begin)
		capFIeta6 = ((double) ( 4.0 * misplacement_X * misplacement_Y ) * de2inzero);

		capFIeta6 = (double)capFIeta6 - ((double) (4.0 * alpha3) * 
		( 3.0 * ( ( pow(misplacement_X, 2.0) * misplacement_Y / 2.0 ) + ( misplacement_X * pow(misplacement_Y, 2.0) / 2.0 ) ) - ( 2.0 * misplacement_X * misplacement_Y ) ) );

		capFIeta6 = (double)capFIeta6 - ((double) (4.0 * alpha2) * 
		( - ( ( pow(misplacement_X, 2.0) * misplacement_Y / 2.0 ) + ( misplacement_X * pow(misplacement_Y, 2.0) / 2.0 ) ) + ( 2.0 * misplacement_X * misplacement_Y ) ) );
		//calculation of eta6 (end)


		CurvRf = ((double) (( 4.0 * derRXX * capFIeta6 ) - ( 4.0 * lambda * XXdex2etasix )) * ( capFIeta6 * capFIeta6 ));

		CurvRf = (double)CurvRf - ((double) (( 4.0 * deLambdaX * capFIeta6 ) - ( 4.0 * lambda * etasixdex )) * ( 2.0 * capFIeta6 * etasixdex ));


		Add2 = ((double) (( 4.0 * RYY * capFIeta6 ) - ( 4.0 * lambda * YYdey2etasix )) * ( capFIeta6 * capFIeta6 ));

		Add2 = (double)Add2 - ((double) (( 4.0 * de2LambdaY * capFIeta6 ) - ( 4.0 * lambda * deyetasix )) * ( 2.0 * capFIeta6 * deyetasix ));


		CurvRf = (double)CurvRf + (double)Add2;


		Add3 = ((double) 4.0 * (( sodeRXY * capFIeta6 ) + 
			                    ( deLambdaX * deyetasix ) - 
								( de2LambdaY * etasixdex) - 
								( lambda * XYdexy2etasix)) );

		Add3 = (double)Add3 * ((double) capFIeta6 * capFIeta6 ); 

		Add3 = (double)Add3 - ((double) (( 4.0 * deLambdaX * capFIeta6 ) - ( 4.0 * lambda * etasixdex )) * ( 2.0 * capFIeta6 * deyetasix ));


		CurvRf = (double)CurvRf + (double)Add3;


		Add4 = ((double) 4.0 * (( secondRYX * capFIeta6) + 
			                    ( de2LambdaY * etasixdex ) - 
					            ( deLambdaX * deyetasix ) - 
					            ( lambda * YXdeyx2etasix )) );

		Add4 = (double)Add4 * ((double) capFIeta6 * capFIeta6); 

		Add4 = (double)Add4 - ((double) (( 4.0 * de2LambdaY * capFIeta6 ) - ( 4.0 * lambda * deyetasix )) * ( 2.0 * capFIeta6 * etasixdex ));


		CurvRf = (double)CurvRf + (double)Add4;

		// calculation of the coefficients of the total curvature (end)

		if ( (double)pow( (double)capFIeta6 , 4.0 ) != 0 ) 

			 SRI.pointer->ResilientCurvature[i1][i2] = ((double) CurvRf / pow( (double)capFIeta6, 4.0) ); // 2011

		else SRI.pointer->ResilientCurvature[i1][i2] = (double)0.0; 

		// 2011 (end)

		// calculate the curvature of the Resilient Signal (end) 


		/// Calculation of the Intensity-Curvature Functional (begin) ///
		double E0 = (double) 4.0 * misplacement_X * misplacement_Y * SRI.pointer->OriginalSignal[i1][i2] * 
			        ((double) - 2.0 * alpha3 + 2.0 * alpha2 );

		double EIN = (double) 4.0 * (SRI.pointer->OriginalSignal[i1][i2] * alpha3 * (3.0 * (pow(misplacement_X, 2.0) * 
			                  misplacement_Y/2.0 + misplacement_X * pow(misplacement_Y, 2.0)/2.0) - 2.0 * misplacement_X *
							  misplacement_Y)) + SRI.pointer->OriginalSignal[i1][i2] * alpha2 * ( (-pow(misplacement_X, 2.0) * 
							  misplacement_Y/2.0 - misplacement_X * pow(misplacement_Y, 2.0)/2.0 + 2.0 * misplacement_X * misplacement_Y)) +

							  4.0 * ( ( (3.0/2.0 * alpha3 * alpha3 - 1.0/2.0 * alpha3 * alpha2 - 3.0/6.0 * alpha3 * alpha2 + 1.0/6.0 * alpha2 * alpha2) *
							  (pow(misplacement_X, 5.0) * misplacement_Y/5.0 + 3.0/8.0 * pow(misplacement_X, 4.0) *
							  pow(misplacement_Y, 2.0) + pow(misplacement_X, 3.0) * pow(misplacement_Y, 3.0)/3.0 + pow(misplacement_X, 2.0) *
							  pow(misplacement_Y, 4.0)/8.0 + pow(misplacement_X, 4.0) * pow(misplacement_Y, 2.0)/8.0 +
							  pow(misplacement_X, 3.0) * pow(misplacement_Y, 3.0)/3.0 + 3.0/8.0 * pow(misplacement_X, 2.0) *
							  pow(misplacement_Y, 4.0) + misplacement_X * pow(misplacement_Y, 5.0)/5.0) +

							  (-4.0 * alpha3 * alpha3 + 2.0 * alpha3 * alpha2 + 4.0/3.0 * alpha3 * alpha2 - 4.0/3.0 * alpha2 * alpha2) * 
							  (pow(misplacement_X, 4.0) * misplacement_Y/4.0 + pow(misplacement_X, 3.0) * pow(misplacement_Y, 2.0)/2.0 +
							  pow(misplacement_X, 2.0) * pow(misplacement_Y, 3.0)/2.0 + misplacement_X * pow(misplacement_Y, 4.0)/4.0) +
							  (2.0 * alpha3 * alpha3 - 2.0 * alpha3 * alpha2 - 8.0 * alpha3 * alpha2 + 4.0 * alpha2 * alpha2) *
							  (pow(misplacement_X, 3.0) * misplacement_Y/3.0 + pow(misplacement_X, 2.0) * pow(misplacement_Y, 2.0)/2.0 + 
							  misplacement_X * pow(misplacement_Y, 3.0)/3.0) + (2.0 * alpha3 * alpha3 - 2.0/3.0 * alpha3 * alpha2 + 8.0 * alpha3 *
							  alpha2 - 16.0/3.0 * alpha2 * alpha2) * (pow(misplacement_X, 2.0) * misplacement_Y/2.0 + misplacement_X *
							  pow(misplacement_Y, 2.0)/2.0) + (-4.0/3.0 * alpha3 * alpha3 + 4.0/3.0 * alpha3 * alpha2 - 8.0/3.0 * alpha3 * alpha2 +
							  8.0/3.0 * alpha2 * alpha2) * (misplacement_X * misplacement_Y)) );

                     
		if ( EIN != 0.0 ) SRI.pointer->ICF[i1][i2] = ((double)E0/EIN);
		else			  SRI.pointer->ICF[i1][i2] = (double)0.0;

		/// Calculation of the Intensity-Curvature Functional (end) ///

		} else if ( (double)SRI.pointer->OriginalSignal[i1][i2] <= TH ) { }

		} // y dim
        
	}  // x dim	
	
	std::cout << "Signal Resilient to Interpolation (SRI) calculated" << endl;
	std::cout << "Curvature of the SRI calculated" << endl;

	double A, A1, A2;
	// calculation of PIC classic (begin)
	for (i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

		if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) { 

		A1 = ((double)(n1-(2.0*PAD))*XPixelSize);

		A2 = ((double)(n2-(2.0*PAD))*YPixelSize);

		A = (double)sqrt( pow(A1, (double)2.0) + pow(A2, (double)2.0) );
        
		TheShift = (double) sqrt( ((double)misplacement_X * misplacement_X) + 
                                  ((double)misplacement_Y * misplacement_Y) );
           
		SRI.pointer->ThePixICClassic[i1][i2] = (double)TheShift * 
	    ((double)tan( (double)SRI.pointer->ClassicCurvature[i1][i2] * 2.0 * 3.1415926535897 ) / A); 
	

		} else if ( (double)SRI.pointer->OriginalSignal[i1][i2] <= TH ) { }

		} // y dim
        
	}  // x dim	
	// calculation of PIC classic (end)


	std::cout << "PIC Classic calculated" << endl;

	// calculation of PIC resilient (begin)
	for (i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim


		if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) { 

		A1 = ((double)(n1-(2.0*PAD))*XPixelSize);

		A2 = ((double)(n2-(2.0*PAD))*YPixelSize);

		A = (double)sqrt( pow(A1, (double)2.0) + pow(A2, (double)2.0) );
        
		TheShift = (double) sqrt( ((double)misplacement_X * misplacement_X) + 
                                  ((double)misplacement_Y * misplacement_Y) );
           
		SRI.pointer->ThePixICResilient[i1][i2] = (double)TheShift * 
	    ((double)tan( (double)SRI.pointer->ResilientCurvature[i1][i2] * 2.0 * 3.1415926535897 ) / A); 


		} else if ( (double)SRI.pointer->OriginalSignal[i1][i2] <= TH ) { }

		} // y dim
        
	}  // x dim	
	// calculation of PIC resilient (end)

	std::cout << "PIC Resilient calculated" << endl;

	// reconstruct the signal -> Classic (begin)
	for (i1=0; i1 < n1; i1++) {// x dim

		for (int i2=0; i2 < n2; i2++) {// y dim

		if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) { 

		SRI.pointer->shifted_OriginalSignal[i1][i2] = 
			
		(double)SRI.pointer->OriginalSignal[i1][i2] + 

		(double)SRI.pointer->ThePixICClassic[i1][i2];
		
		} else if ( (double)SRI.pointer->OriginalSignal[i1][i2] <= TH ) { }

		} // y dim
        
	}  // x dim	
	// reconstruct the signal -> Classic (end)


	// reconstruct the signal -> Resilient (begin)
	for (i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

		if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) { 

		SRI.pointer->the_SRI_shifted_OriginalSignal[i1][i2] = 
			
		(double)SRI.pointer->OriginalSignal[i1][i2] + 

		(double)SRI.pointer->ThePixICResilient[i1][i2];
		
		} else if ( (double)SRI.pointer->OriginalSignal[i1][i2] <= TH ) { }

		} // y dim
        
	}  // x dim	
	// reconstruct the signal -> Resilient (end)

	// reconstruct Hybrid Signal (begin)
	for (i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

		if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) { 


		if ( (double)abs( (double)SRI.pointer->ThePixICClassic[i1][i2] ) <= 
			
			 (double)abs( (double)SRI.pointer->ThePixICResilient[i1][i2] ) )
		{ 
    
		SRI.pointer->HybridSignal[i1][i2] = (double)SRI.pointer->shifted_OriginalSignal[i1][i2];
			
		} else 
		if ( (double)abs( (double)SRI.pointer->ThePixICClassic[i1][i2] ) > 
			
			 (double)abs( (double)SRI.pointer->ThePixICResilient[i1][i2] ) )
		{ 

		SRI.pointer->HybridSignal[i1][i2] = (double)SRI.pointer->the_SRI_shifted_OriginalSignal[i1][i2];

		}

		} else if ( (double)SRI.pointer->OriginalSignal[i1][i2] <= TH ) { }

		} // y dim
        
	}  // x dim	
   // reconstruct Hybrid Signal (end)


	std::cout << "Signals reconstructed" << endl;

	// compute SE (begin)
	double SE_sum = 0.0;
	long int counter = 0;
	
	for (i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

		if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) { 

		counter++;

		SRI.pointer->SE[i1][i2] = (double) sqrt( ( SRI.pointer->OriginalSignal[i1][i2] - SRI.pointer->shifted_OriginalSignal[i1][i2] ) * 
			                                     ( SRI.pointer->OriginalSignal[i1][i2] - SRI.pointer->shifted_OriginalSignal[i1][i2] ) );  

		SE_sum = SRI.pointer->SE[i1][i2] + SE_sum;

		}

		} // y dim
        
	}  // x dim	
	// compute SE (end)

	std::cout << "SE with no SRI is: " << ((double)SE_sum / (counter))  << endl;
	std::cout << endl;

	double errorSE = ((double)SE_sum / (counter));

	// compute SE_SRI (begin)
	double SE_SRI_sum = 0.0;
	counter = 0;

	for (i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

		if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) { 

		counter++;

		SRI.pointer->SE_SRI[i1][i2] = (double) sqrt( ( SRI.pointer->OriginalSignal[i1][i2] - SRI.pointer->the_SRI_shifted_OriginalSignal[i1][i2] ) * 
			                                         ( SRI.pointer->OriginalSignal[i1][i2] - SRI.pointer->the_SRI_shifted_OriginalSignal[i1][i2] ) );  

		SE_SRI_sum = SRI.pointer->SE_SRI[i1][i2] + SE_SRI_sum;

		}

		} // y dim
        
	}  // x dim
	// compute SE_SRI (end)

	std::cout << "SE with SRI is: " << ((double)SE_SRI_sum / (counter))  << endl;
	std::cout << endl;


	double errorSE_SRI = ((double)SE_SRI_sum / ( counter ));

	double DIFF = ((double) errorSE_SRI -  errorSE);

	fprintf(savedata, "%e\t %e\t %e\t %e\t %e\n", misplacement_X, misplacement_Y, errorSE, errorSE_SRI, DIFF);

    STEP_A = ((double)STEP_A + 0.0001);
             
    STEP_MX = ((double)STEP_MX + 0.0095);
            
    STEP_MY = ((double)STEP_MY + 0.0095);
            
	}  //---> major for loop (end) <---//

	std::cout << "End of Computation..." << endl;
	std::cout << endl;

	fprintf(savedata,"%s\n", "End of Computation...");
	fprintf(savedata,"\n");

	fclose(savedata);

	free(ALPHA3);
	free(ALPHA2);
	delete SRI.pointer;
	SRI.~SRI2D2013();
	} // processing (end)

	} // run the program (end)

	system("java processCompleted");

	return 0;
} // end of main 
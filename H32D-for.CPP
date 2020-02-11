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


//  Project Title: Bivariate Quadratic SRI Interpolation

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

if (argc < 9)  { std::cout << endl;
				 std::cout << "Please type the image file name" << endl;
				 std::cout << "Please make sure that the image format is Analyze 'double': 64 bits real" << endl;
				 std::cout << "Before running the program, please make sure that the image is padded of 'n >= 0'";
				 std::cout << "number of pixels along X and Y" << endl;
				 std::cout << "Please enter the number of pixels along the X direction (integer)" << endl;
				 std::cout << "Please enter the number of pixels along the Y direction (integer)" << endl;
				 std::cout << "Please enter the pixel size along the X direction (double)" << endl;
				 std::cout << "Please enter the pixel size along the Y direction (double)" << endl;
				 std::cout << "Please enter the a constant (double)" << endl;
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
	double the_A_const = atof(argv[6]);

	char imageFileName[128];

	int PAD = atoi(argv[7]);

	unsigned char Fyn = 'n';

	Fyn = *argv[8];

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
	std::cout << "The a constant is: " << atof(argv[6]) << endl;
	std::cout << "The 'n' number of pixels along X and Y which you entered to pad the image is: " << atoi(argv[7]) << endl;
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
	fprintf(savedata,"%s%lf\n", "The a constant is: ", the_A_const);
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
	sprintf(command, "%s%s%s%d%s%d%s%c%s%s%s%s%s%s%s%s", "java -jar AlphaBetaConvolve2013.jar ", 
		                                                   imageFileName, " ", n1, " ", n2, " ", 
												      Fyn, " ", "alpha1.img", " ", "alpha2.img", 
												            " ", "beta1.img", " ", "beta2.img"); 
	system(command);
	/// run JAVA (end)

	
	/// allocate memory & store ALPHAs & BETAs (begin)
	double * ALPHA1 = 0;
	double * ALPHA2 = 0;

	/// allocate ALPHAs & BETAs (begin)
	if ((ALPHA1 = (double *) calloc( n1*n2, sizeof(double)) ) == NULL)
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

		*(ALPHA1 + index) = (double)0.0;
    	

		} // y dim
        
	}  // x dim 

	}//else

	if ((ALPHA2 = (double *) calloc( n1*n2, sizeof(double)) ) == NULL)
	{

	std::cout << "Not enough memory to allocate Image data, Exit." << endl;
    fprintf(savedata,"%s\n", "Not enough memory to allocate Image data, Exit.");

	fclose(savedata);
	
	free(ALPHA1);
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

	double * BETA1 = 0;
	double * BETA2 = 0;

	/// allocate ALPHAs & BETAs (begin)
	if ((BETA1 = (double *) calloc( n1*n2, sizeof(double)) ) == NULL)
	{

	std::cout << "Not enough memory to allocate Image data, Exit." << endl;
    fprintf(savedata,"%s\n", "Not enough memory to allocate Image data, Exit.");

	fclose(savedata);

	free(ALPHA1);
	free(ALPHA2);
	SRI.~SRI2D2013();
	
	exit(0);

	} else { // else

	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

		int index = ((int) i2*n1 + i1); 

		*(BETA1 + index) = (double)0.0;
    	

		} // y dim
        
	}  // x dim 

	}//else

	if ((BETA2 = (double *) calloc( n1*n2, sizeof(double)) ) == NULL)
	{

	std::cout << "Not enough memory to allocate Image data, Exit." << endl;
    fprintf(savedata,"%s\n", "Not enough memory to allocate Image data, Exit.");

	fclose(savedata);
	
	free(ALPHA1);
	free(ALPHA2);
	free(BETA1);
	SRI.~SRI2D2013();

	exit(0);

	} else { // else


	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim
		
		int index = ((int) i2*n1 + i1); 

		*(BETA2 + index) = (double)0.0;


		} // y dim
        
	}  // x dim 

	}//else
	/// allocate ALPHAs & BETAs (end)

	/// read alpha & beta (begin)
	FILE * readFile;
	char inputFile[128];
	double readdata;
	
	sprintf(inputFile, "%s","alpha1.img");

	if ((readFile = fopen(inputFile,"rb"))==NULL)
	{

		std::cout << "Cannot open input file, Now Exit..." << endl;
		fprintf(savedata,"%s\n", "Cannot open input file, Now Exit...");
		
		free(ALPHA1);
		free(ALPHA2);
		free(BETA1);
		free(BETA2);
		SRI.~SRI2D2013();
		
		exit(0);
		
	} else  { // (read)


	for( int i1=0; i1 < n1; i1++ ) { // (a)

		for( int i2=0; i2 < n2; i2++ ) {
	
		int index = ((int) i2*n1 + i1); 

		fread(&readdata, sizeof(double),1, readFile);

		*(ALPHA1 + index) = (double)readdata;

		}

	} // (a)

	fclose(readFile);

	} // (read)

	sprintf(inputFile, "%s","alpha2.img");

	if ((readFile = fopen(inputFile,"rb"))==NULL)
	{

		std::cout << "Cannot open input file, Now Exit..." << endl;
		fprintf(savedata,"%s\n", "Cannot open input file, Now Exit...");

		free(ALPHA1);
		free(ALPHA2);
		free(BETA1);
		free(BETA2);
		SRI.~SRI2D2013();

		exit(0);

	} else  { // (read)


	for( int i1=0; i1 < n1; i1++ ) { // (a)

		for( int i2=0; i2 < n2; i2++ ) {
	
		int index = ((int) i2*n1 + i1); 

		fread(&readdata, sizeof(double),1, readFile);

		*(ALPHA2 + index) = (double)readdata;

		}

	} // (a)

	fclose(readFile);

	} // (read)

	sprintf(inputFile, "%s","beta1.img");

	if ((readFile = fopen(inputFile,"rb"))==NULL)
	{

		std::cout << "Cannot open input file, Now Exit..." << endl;
		fprintf(savedata,"%s\n", "Cannot open input file, Now Exit...");
		
		free(ALPHA1);
		free(ALPHA2);
		free(BETA1);
		free(BETA2);
		SRI.~SRI2D2013();
		
		exit(0);
		
	} else  { // (read)


	for( int i1=0; i1 < n1; i1++ ) { // (a)

		for( int i2=0; i2 < n2; i2++ ) {
	
		int index = ((int) i2*n1 + i1); 

		fread(&readdata, sizeof(double),1, readFile);

		*(BETA1 + index) = (double)readdata;

		}

	} // (a)

	fclose(readFile);

	} // (read)

	sprintf(inputFile, "%s","beta2.img");

	if ((readFile = fopen(inputFile,"rb"))==NULL)
	{

		std::cout << "Cannot open input file, Now Exit..." << endl;
		fprintf(savedata,"%s\n", "Cannot open input file, Now Exit...");

		free(ALPHA1);
		free(ALPHA2);
		free(BETA1);
		free(BETA2);
		SRI.~SRI2D2013();

		exit(0);

	} else  { // (read)


	for( int i1=0; i1 < n1; i1++ ) { // (a)

		for( int i2=0; i2 < n2; i2++ ) {
	
		int index = ((int) i2*n1 + i1); 

		fread(&readdata, sizeof(double),1, readFile);

		*(BETA2 + index) = (double)readdata;

		}

	} // (a)

	fclose(readFile);

	} // (read)
	/// read alpha & beta (end)
	/// allocate memory & store ALPHAs & BETAs (end)

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
	double alpha1, alpha2;
	double a, b, c, d, e;
	double H3_2D_1, H3_2D_2;
	double TheShift;
	
	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

		if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) { 


	    int index = ((int) i2*n1 + i1); 

	    alpha1 =  (double)*(ALPHA1 + index);

	    alpha2 =  (double)*(ALPHA2 + index);


		// compute polynomial coefficients (begin)
		a = ((double) -2.0 * the_A_const * (misplacement_X + misplacement_Y) * (misplacement_X + misplacement_Y));

		b = ((double) 0.5 * (1.0 + the_A_const));

		c = ((double) the_A_const * (misplacement_X + misplacement_Y) * (misplacement_X + misplacement_Y));

		d = ((double) -( 2.0 * the_A_const + 0.5 ) * (misplacement_X + misplacement_Y));

		e = ((double) (3.0/4.0) * ( 1.0 + the_A_const));
		// compute polynomial coefficients (end)

		// compute the h functions without transfer function (begin) 
		H3_2D_1 =  ((double) ( a + b ) * alpha1 ) ;

		H3_2D_2 =  ((double) ( c + d + e ) * alpha2 );
		// compute the h functions without transfer function (end) 

		SRI.pointer->shifted_OriginalSignal[i1][i2] = 
			
		(double)SRI.pointer->OriginalSignal[i1][i2] + ((double)H3_2D_1 + (double)H3_2D_2);
		
		
		TheShift = (double)sqrt( ((double)misplacement_X * misplacement_X) + 
			                     ((double)misplacement_Y * misplacement_Y) );

		// calculate curvature of model interpolation function (Classic)
		SRI.pointer->ClassicCurvature[i1][i2] = 
		
		((double)4.0 * ( (- 4.0 * the_A_const * alpha1) + (2.0 * the_A_const * alpha2) ) );

		} else if ( (double)SRI.pointer->OriginalSignal[i1][i2] <= TH ) { }

		} // y dim
        
	}  // x dim
	
	std::cout << "Image shifted of the given misplacement" << endl;
	std::cout << "Curvature of model interpolation function calculated" << endl;
	// shift the image of the given misplacement (end)
	// calculate curvature of model interpolation function (end)



	// calculate the signal resilient to interpolation (begin)
	double beta1, beta2;
	double f, e1, e2, e3;
	double gamma1, gamma2;
	double coeffA, curvA, curvB, curvC; 
	double Ryx, Rxy, Ryy, Rxx;
	double curvD, curvE, term1, coeffB;
	double term2, coeffC, term12, term3;
	double term4, term5, term6, NonDev;
	double ThecurvC, ThecurvD, ThecurvE;
	double TheTerm1, ThecoeffB, Theterm2;
	double ThecoeffC, Theterm12, Theterm3;
	double Theterm4, Theterm5, Theterm6;
	double Theterm7, de, de1, de2, Ryydep;
	double d3, deg1y, deg2y, ThePI2;
	double de4, de5, de6, Rxxdep, de7;
	double deg1x, deg2x, ThePI1;


	for (i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim


		if ( (double)SRI.pointer->OriginalSignal[i1][i2] > TH ) { 

			
		 int index = ((int) i2*n1 + i1); 

	     alpha1 =  (double)*(ALPHA1 + index);

	     alpha2 =  (double)*(ALPHA2 + index);

		 beta1 = (double)*(BETA1 + index);

		 beta2 = (double)*(BETA2 + index);


		 a = ((double)( misplacement_X * misplacement_X * misplacement_X * misplacement_Y) / 3.0);


		 b = ((double)( misplacement_X * misplacement_X * misplacement_Y * misplacement_Y) / 2.0);


		 c = ((double)( misplacement_X * misplacement_Y * misplacement_Y * misplacement_Y) / 3.0);


		 d = ((double)0.5 * misplacement_X * misplacement_Y * ( the_A_const + 1.0 )); 


		 e1 = - ((double) 2.0 * the_A_const + 0.5 );


		 e2 = ((double)( misplacement_X * misplacement_X * misplacement_Y ) / 2.0); 


		 e3 = ((double)( misplacement_X * misplacement_Y * misplacement_Y ) / 2.0); 


		 e =  ((double) e1 * ( e2 + e3 ));


		 f = ((double) 3.0 * misplacement_X * misplacement_Y * ( the_A_const + 1.0 ) / 4.0); 

		 
		 gamma1 = - ((double)( 2.0 * the_A_const * ( a + b + c ) ) + d);


		 gamma2 = ((double)( (the_A_const * ( a + b + c )) + e + f ));


		if ( ((double)gamma1 + gamma2) != 0.0 )
			 SRI.pointer->ResilientSignal[i1][i2] = - ((double)( beta1 * gamma1 + beta2 * gamma2 ) / ( gamma1 + gamma2 ));
		else SRI.pointer->ResilientSignal[i1][i2] =  (double)SRI.pointer->OriginalSignal[i1][i2];
		// calculate the signal resilient to interpolation (end)


		// calculate the curvature of the Resilient Signal (begin) 
		a = ((double)( misplacement_X * misplacement_X * misplacement_X * misplacement_Y) / 3.0);


		b = ((double)( misplacement_X * misplacement_X * misplacement_Y * misplacement_Y) / 2.0);


		c = ((double)( misplacement_X * misplacement_Y * misplacement_Y * misplacement_Y) / 3.0);

		
		d = ((double)0.5 * misplacement_X * misplacement_Y * ( the_A_const + 1.0 )); 


		e1 = - ((double) 2.0 * the_A_const + 0.5 );


		e2 = ((double)( misplacement_X * misplacement_X * misplacement_Y ) / 2.0); 


		e3 = ((double)( misplacement_X * misplacement_Y * misplacement_Y ) / 2.0); 

	
		e =  ((double)e1 * ( e2 + e3 ));


		f = ((double) 3.0 * misplacement_X * misplacement_Y * ( the_A_const + 1.0 ) / 4.0); 

		// Eq. 1.c
		gamma1 = - ((double)( 2.0 * the_A_const * ( a + b + c ) ) + d); 

		// Eq. 1.d 
		gamma2 = ((double)( (the_A_const * ( a + b + c )) + e + f ));


		// 2011 (begin)
		// calculate Ryx = (dR/dydx)
		coeffA = ((double) (misplacement_X * misplacement_X) + 
			               (2.0 * misplacement_X * misplacement_Y) + 
				           (misplacement_Y * misplacement_Y) );

		// Eq. 8.b dgamma1dydx = dgamma1dxdy
		curvA = ((double)( - 2.0 * the_A_const * coeffA ) + 0.5 * (the_A_const + 1.0) );


		// Eq. 11 dgamma2dydx = dgamma2dxdy
		curvB = ((double) the_A_const * coeffA - 
			              ((2.0 * the_A_const + 0.5) * (misplacement_X + misplacement_Y)) + 
				          (3.0/4.0) * (the_A_const + 1.0));


		Ryx = ((double) (beta1 * curvA + beta2 * curvB) * (gamma1 + gamma2));


		curvC = ((double) ( (misplacement_X * misplacement_X * misplacement_X) / 3.0 ) + 
			                (misplacement_X * misplacement_X * misplacement_Y) + 
				            (misplacement_X * misplacement_Y * misplacement_Y) );


		// Eq. 3 dgamma1dy
		curvD = ((double)(- 2.0 * the_A_const * curvC) + (0.5 * misplacement_X * (the_A_const + 1.0)) );

		// Eq. 5 dgamma2dy
		curvE = ((double) the_A_const * curvC - 
			             (2.0 * the_A_const + 0.5) * ( (misplacement_X * misplacement_X / 2.0) + (misplacement_X * misplacement_Y) ) + 
			             ((3.0/4.0) * misplacement_X * (the_A_const + 1.0)) );

		
		term1 = ((double)(beta1 * curvD + beta2 * curvE));


		coeffB = ((double) (misplacement_X * misplacement_X * misplacement_Y) + 
			               (misplacement_X * misplacement_Y * misplacement_Y) + 
				           (misplacement_Y * misplacement_Y * misplacement_Y / 3.0) );

		// Eq. 2 dgamma1dx
		term2 = ((double) ( - 2.0 * the_A_const * coeffB ) + (0.5 * misplacement_Y * (the_A_const + 1.0)) );

		// Eq. 4 dgamma2dx
		coeffC = ((double) (the_A_const * coeffB) - 
			     (2.0 * the_A_const + 0.5) * ( (misplacement_X * misplacement_Y) + (misplacement_Y * misplacement_Y / 2.0) ) + 
				 ((3.0/4.0) * misplacement_Y * (the_A_const + 1.0)) );

		// Eq. 2 + Eq. 4 (dgamma1dx + dgamma2dx)
		term12 = ((double) term2 + coeffC);


		Ryx = (double)Ryx + ((double)term1 * term12);

		term3 = ((double)(beta1 * term2) + (beta2 * coeffC));

		// Eq. 3 + Eq. 5 (dgamma1dy + dgamma2dy)
		term4 = ((double)curvD + curvE);


		Ryx = (double)Ryx - ((double)term3 * term4);

		term5 = ((double)(beta1 * gamma1) + (beta2 * gamma2));

		// Eq. 8.b + Eq. 11 (dgamma1dydx + dgamma2dydx)
		term6 = ((double)curvA + curvB); 

		Ryx = (double)Ryx - ((double)term5 * term6);

		NonDev = ((double)term1 * (gamma1 + gamma2) - (term5 * term4));

		Ryx = (double)Ryx * ((double)(gamma1 + gamma2) * (gamma1 + gamma2));

		Ryx = (double)Ryx - ((double)(NonDev * 2.0 * term12) * (gamma1 + gamma2));


		// preserve the minus sign at the end
		if ( (double)pow( ((double)gamma1 + gamma2) , 4.0 ) != 0 ) 

			Ryx = - (double)Ryx / ( (double)pow( ((double)gamma1 + gamma2) , 4.0 ) );

		else Ryx = (double)0.0; 


		// calculate Rxy = (dR/dxdy)
                                  // Eq. 8.b           // Eq. 11 = Eq. 10  
		Rxy = ((double)( ( beta1 * curvA ) + ( beta2 * curvB ) ) * (gamma1 + gamma2));


		ThecurvC = ((double)(misplacement_X * misplacement_X * misplacement_Y) + 
			                (misplacement_X * misplacement_Y * misplacement_Y) + 
				            (misplacement_Y * misplacement_Y * misplacement_Y / 3.0) );

		// Eq. 2 dgamma1dx
		ThecurvD = ((double)(- 2.0 * the_A_const * ThecurvC) + (0.5 * misplacement_Y * (the_A_const + 1.0)) );


		// Eq. 4 dgamma2dx
		ThecurvE = ((double) the_A_const * ThecurvC - 
			       (2.0 * the_A_const + 0.5) * ( (misplacement_X * misplacement_Y) + (misplacement_Y * misplacement_Y / 2.0) ) + 
			       ((3.0/4.0) * misplacement_Y * (the_A_const + 1.0)) );


		TheTerm1 = ((double) ( beta1 * ThecurvD) + ( beta2 * ThecurvE ));


		ThecoeffB = ((double) (misplacement_X * misplacement_X * misplacement_X / 3.0) + 
			                  (misplacement_X * misplacement_X * misplacement_Y) + 
					          (misplacement_X * misplacement_Y * misplacement_Y) );

		//Eq. 3 dgamma1dy
		Theterm2 = ((double) ( - 2.0 * the_A_const * ThecoeffB ) + (0.5 * misplacement_X * (the_A_const + 1.0)) );

		// Eq. 5 dgamma2dy
		ThecoeffC = ((double) (the_A_const * ThecoeffB) - 
			                  (2.0 * the_A_const + 0.5) * ( (misplacement_X * misplacement_X / 2.0) + (misplacement_X * misplacement_Y) ) + 
					          ((3.0/4.0) * misplacement_X * (the_A_const + 1.0)) );

		Theterm12 = ((double)Theterm2 + ThecoeffC);


		Rxy = (double)Rxy + ((double)TheTerm1 * Theterm12);

		                             // Eq. 3 dgamma1dy   Eq. 5 dgamma2dy
		Theterm3 = ((double)(beta1 * Theterm2) + (beta2 * ThecoeffC)); 

		// Eq. 4 dgamma2dx
		Theterm4 = ((double) the_A_const * ThecurvC - 
		                     (2.0 * the_A_const + 0.5) * ( (misplacement_X * misplacement_Y) + (misplacement_Y * misplacement_Y / 2.0) ) + 
			                 ((3.0/4.0) * misplacement_Y * (the_A_const + 1.0)) );


		           // Eq. 2 dgamma1dx +  Eq. 4 dgamma2dx
		Theterm5 = ((double) ThecurvD + Theterm4);


		Rxy = (double)Rxy - ((double) Theterm3 * Theterm5); 


		Theterm6 = ((double)( beta1 * gamma1 ) + ( beta2 * gamma2));


		            // dgamma1dxdy + dgamma2dxdy
		Theterm7 = ((double) curvA + curvB);


		Rxy = (double)Rxy - ((double) Theterm6 * Theterm7);

		NonDev = ((double)TheTerm1 * (gamma1 + gamma2) - (Theterm6 * Theterm5));

		Rxy = (double)Rxy * ((double) (gamma1 + gamma2) * (gamma1 + gamma2));

		Rxy = (double)Rxy - ((double) (NonDev * 2.0 * Theterm12) * (gamma1 + gamma2) );


		// preserve the minus sign at the end
		if ( (double)pow( ((double)gamma1 + gamma2) , 4.0 ) != 0 ) 

			Rxy = - (double)Rxy / ( (double)pow( ((double)gamma1 + gamma2) , 4.0 ) );

		else Rxy = (double)0.0; 


		// calculate Ryy = (dR/dydy)
		de = ((double) (misplacement_X * misplacement_X) + (2.0 * misplacement_X * misplacement_Y) );

		de1 = - ((double)2.0 * the_A_const * de);

		de2 = (double)the_A_const * de - ((double) ( 2.0 * the_A_const + 0.5 ) * misplacement_X);

		Ryydep = ((double) ( ( beta1 * de1 ) + ( beta2 * de2 ) ) * ( gamma1 + gamma2 ) );

		// see term1 = (beta1 * curvD + beta2 * curvE);
		Ryydep = (double)Ryydep + ( (double)term1 * ( curvD + curvE ) ); 
		// the same term is summed and subtracted
		Ryydep = (double)Ryydep - ( (double)term1 * ( curvD + curvE ) );
		
		Ryydep = (double)Ryydep - ( (double) ( beta1 * gamma1  +  beta2 * gamma2 ) * ( de1 + de2 ) ); 

		                                          // Eq. 3 + Eq. 5 (dgamma1dy + dgamma2dy)
		d3=  ((double) 2.0 * ( gamma1 + gamma2 ) * ( curvD + curvE ) ); 


		deg1y = (double)curvD;
		deg2y = (double)curvE;

		ThePI2 = ((double) ( beta1 * deg1y + beta2 * deg2y ) * ( gamma1 + gamma2 ) );

		ThePI2 = (double)ThePI2 - ((double) ( beta1 * gamma1 + beta2 * gamma2 ) * ( deg1y + deg2y ) );

		Ryy = ( (double)Ryydep * (double)pow( ( gamma1 + gamma2 ) , 2.0) ) - ((double) ThePI2 * d3 ) ;


		// preserve the minus sign at the end
		if ( (double)pow( ((double)gamma1 + gamma2) , 4.0 ) != 0 ) 

			Ryy = - (double)Ryy / ( (double)pow( ((double)gamma1 + gamma2) , 4.0 ) );

		else Ryy = (double)0.0; 


		// calculate Rxx = (dR/dxdx)
		de4 = ( (double) (2.0 * misplacement_X * misplacement_Y) + (misplacement_Y * misplacement_Y) );

		de5 = - ((double)2.0 * the_A_const * de4);

		de6 = ((double)the_A_const * de4) - ( (double) ( 2.0 * the_A_const + 0.5 ) * misplacement_Y );

		Rxxdep = ((double) ( ( beta1 * de5 ) + ( beta2 * de6 ) ) * ( gamma1 + gamma2 ) ); 

		                                                // Eq. 2 dgamma1dx     // Eq. 4 dgamma2dx
		Rxxdep = (double)Rxxdep + ( (double) (( beta1 * ThecurvD ) + ( beta2 * ThecurvE )) * ( ThecurvD + ThecurvE ) ); 

		//the same term is summed and subtracted
		Rxxdep = (double)Rxxdep - ( (double) (( beta1 * ThecurvD ) + ( beta2 * ThecurvE )) * ( ThecurvD + ThecurvE ) ); 

		Rxxdep = (double)Rxxdep - ( (double) ( ( beta1 * gamma1 ) + ( beta2 * gamma2 ) ) * ( de5 + de6 ) );

		// Eq. 25                                    dgamma1dx + dgamma2dx
		de7 = ((double) 2.0 * ( gamma1 + gamma2 ) * ( ThecurvD + ThecurvE )); 

		deg1x = (double)ThecurvD; // Eq. 2 dgamma1dx

		deg2x = (double)ThecurvE; // Eq. 4 dgamma2dx

		// Eq. 16
		ThePI1 = ((double) ( ( beta1 * deg1x ) + ( beta2 * deg2x ) ) * ( gamma1 + gamma2 ) ); 

		ThePI1 = (double)ThePI1 - ( (double)( beta1 * gamma1 + beta2 * gamma2 ) * ( deg1x + deg2x ) ); 

		Rxx = ( (double)Rxxdep * (double)pow( (gamma1 + gamma2), 2.0 ) ) - ( (double)ThePI1 * de7 ); 


		// preserve the minus sign at the end
		if ( (double)pow( ((double)gamma1 + gamma2) , 4.0 ) != 0 ) 

			Rxx = - (double)Rxx / ( (double)pow( ((double)gamma1 + gamma2) , 4.0 ) );

		else Rxx = (double)0.0; 

		// 2011 (end)

		SRI.pointer->ResilientCurvature[i1][i2] = ((double)Rxx + Ryy + Rxy + Ryx);
		// calculate the curvature of the Resilient Signal (end) 

		/// Calculation of the Intensity-Curvature Functional (begin) ///
		double E0 = (double)4.0 * misplacement_X * misplacement_Y * SRI.pointer->OriginalSignal[i1][i2] *
                    ((double) -4.0 * alpha1 * the_A_const + 2.0 * the_A_const * alpha2);

		double EIN = (double) 4.0 * ((double) -4.0 * alpha1 * the_A_const + 2.0 * the_A_const * alpha2) *
			       (  misplacement_X * misplacement_Y * SRI.pointer->OriginalSignal[i1][i2] +
					  alpha1 * (-2.0 * the_A_const * (misplacement_X * misplacement_X * misplacement_X * misplacement_Y/3.0 + 
					  misplacement_X * misplacement_X * misplacement_Y * misplacement_Y/2.0 + 
					  misplacement_X * misplacement_Y * misplacement_Y * misplacement_Y/3.0) +
					  1.0/2.0 * misplacement_X * misplacement_Y * ( the_A_const + 1.0 )) +
					  
					  alpha2 * (the_A_const * (misplacement_X * misplacement_X * misplacement_X * misplacement_Y/3.0 +
					  misplacement_X * misplacement_X * misplacement_Y * misplacement_Y/2.0 + 
					  misplacement_X * misplacement_Y * misplacement_Y * misplacement_Y/3.0) - 
					  (2.0 * the_A_const + 1.0/2.0) * (misplacement_X * misplacement_X * misplacement_Y/2.0 + 
					  misplacement_X * misplacement_Y * misplacement_Y/2.0) + 
					  (3.0/4.0) * misplacement_X * misplacement_Y * ( the_A_const + 1.0 ) )   
					);

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

	free(ALPHA1);
	free(ALPHA2);
	free(BETA1);
	free(BETA2);

	delete SRI.pointer;
	SRI.~SRI2D2013();
	} // processing (end)

	} // run the program (end)

	system("java processCompleted");

	return 0;
} // end of main 
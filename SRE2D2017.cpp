//  This file contains sourcecode distributed as freeware. 
//  The intellectual property of the sourcecode is shown 
//  here to belong to Carlo Ciulla.

// Disclaimer: 

// The website here named www.sourcecodewebsiteCarloCiulla.com 2013 [1] does not intend 
// to convey the meaning of profit making for what pertains to the content
// provided. --->>> Instead, when the content is downloaded, the user(s) are
// kindly invited to donate money to charity organizations involved in 
// helping people in need of food and water. <<<---


// The Novel Re-sampling Locations have been sized to be a fraction of 
// the pixel size. The programs presented here confirm both concepts and 
// implications brought to knowledge through the unifying theory [1].

// Reference:

// [1] Carlo Ciulla "Improved Signal and Image Interpolation in Biomedical Applications: 
// The Case of Magnetic Resonance Imaging (MRI)." Medical Information Science 
// Reference - IGI Global Publisher - March 2009; ISBN: 978 - 160566202 - 2.

//  Project Title: Bivariate Linear (Bivariate Linear SRE-based Interpolation)
#define _CRT_SECURE_NO_WARNINGS

#include < iostream >
#include < fstream >
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

#define NSCALE 1

using namespace std;


class SRE2D2013 {

	int n1; // matrix size x
	int n2; // matrix size y

public:

	int getNofPixelsX(void) { return this->n1; };

	int getNofPixelsY(void) { return this->n2; };

	void setNofPixelsX(int x) { this->n1 = x; };

	void setNofPixelsY(int y) { this->n2 = y; };

public:

	struct data {

		double **fMRI; // pointer to the matrix entry 

		double **scaledfMRI; // pointer to the matrix entry
		
		double **Xsre; // pointer to the matrix entry 
	
		double **Ysre; // pointer to the matrix entry 

		double **shifted_fMRI; // pointer to the matrix entry 
	
		double **SE; // pointer to the matrix entry 

		double **DELTA; // pointer to the matrix entry 

		double **the_SRE_shifted_fMRI; // pointer to the matrix entry

		double **SE_SRE; // pointer to the matrix entry 

		double **X_recomputed; // pointer to the matrix entry 

		double **Y_recomputed; // pointer to the matrix entry

		double **X_recomputed_scaled; // pointer to the matrix entry 

		double **Y_recomputed_scaled; // pointer to the matrix entry

		double **ICF; // pointer to the matrix entry

		double **Y; // pointer to the matrix entry

		double **X; // pointer to the matrix entry

		double **TF; // pointer to the matrix entry

		double **Xt; // pointer to the matrix entry

	}*pointer; // pointer to the matrices

public:

	SRE2D2013(int x, int y) : n1(x), n2(y) { };// constructor 
	
	void allocateData();

	void save();

	~SRE2D2013() { } // destructor

};

void SRE2D2013::allocateData() { // allocate data


	 // (1) allocate struct 'data' (begin)
	 pointer = new data;
			
	 pointer->fMRI = new double*[this->n1];

	 pointer->scaledfMRI = new double*[this->n1];

	 pointer->Xsre = new double*[this->n1];

	 pointer->Ysre = new double*[this->n1];

	 pointer->shifted_fMRI = new double*[this->n1];

	 pointer->SE = new double*[this->n1];

	 pointer->DELTA = new double*[this->n1];

	 pointer->the_SRE_shifted_fMRI = new double*[this->n1];

	 pointer->SE_SRE = new double*[this->n1];

	 pointer->X_recomputed = new double*[this->n1];

	 pointer->Y_recomputed = new double*[this->n1];

	 pointer->X_recomputed_scaled = new double*[this->n1];

	 pointer->Y_recomputed_scaled = new double*[this->n1];

	 pointer->ICF = new double*[this->n1];

	 pointer->Y = new double*[this->n1];

	 pointer->X = new double*[this->n1];

	 pointer->TF = new double*[this->n1];

	 pointer->Xt = new double*[this->n1];

	

	 for( int v=0; v < this->n1; v++ ) { // (1)
		 
		 pointer->fMRI[v] = new double[this->n2];

		 pointer->scaledfMRI[v] = new double[this->n2];

		 pointer->Xsre[v] = new double[this->n2];

		 pointer->Ysre[v] = new double[this->n2];

		 pointer->shifted_fMRI[v] = new double[this->n2];

		 pointer->SE[v] = new double[this->n2];

		 pointer->DELTA[v] = new double[this->n2];

		 pointer->the_SRE_shifted_fMRI[v] = new double[this->n2];

		 pointer->SE_SRE[v] = new double[this->n2];

		 pointer->X_recomputed[v] = new double[this->n2];

		 pointer->Y_recomputed[v] = new double[this->n2];

		 pointer->X_recomputed_scaled[v] = new double[this->n2];

		 pointer->Y_recomputed_scaled[v] = new double[this->n2];

		 pointer->ICF[v] = new double[this->n2];

		 pointer->Y[v] = new double[this->n2];

		 pointer->X[v] = new double[this->n2];

		 pointer->TF[v] = new double[this->n2];

		 pointer->Xt[v] = new double[this->n2];

	
	  } // (1) allocate struct 'data' (end)


		// (2) initialize (begin)
		for(int v=0; v < this->n1; v++ ) { // (a)

			for( int f=0; f < this->n2 ; f++ ) { // (b)
		 
			pointer->fMRI[v][f] = (double)0.0;

			pointer->scaledfMRI[v][f] = (double)0.0;

			pointer->Xsre[v][f] = (double)0.0;

			pointer->Ysre[v][f] = (double)0.0;

			pointer->shifted_fMRI[v][f] = (double)0.0;

			pointer->SE[v][f] = (double)0.0;

			pointer->DELTA[v][f] = (double)0.0;

			pointer->the_SRE_shifted_fMRI[v][f] = (double)0.0;

			pointer->SE_SRE[v][f] = (double)0.0;

			pointer->X_recomputed[v][f] = (double)0.0;

			pointer->Y_recomputed[v][f] = (double)0.0;

			pointer->X_recomputed_scaled[v][f] = (double)0.0;

			pointer->Y_recomputed_scaled[v][f] = (double)0.0;

			pointer->ICF[v][f] = (double)0.0;

			pointer->Y[v][f] = (double)1.0;

			pointer->X[v][f] = (double)1.0;

			pointer->TF[v][f] = (double)0.0;

			pointer->Xt[v][f] = (double)1.0;


			 } //(b)

		 } //(a)
		// (2) initialize (end)

} // allocate data


void SRE2D2013::save() { // saveImages

	FILE * savedata;
	char outputFile[128];
	
	sprintf(outputFile, "%s","fMRI.img");

	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->fMRI[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)


	
	sprintf(outputFile, "%s","Xsre.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->Xsre[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)
	


	sprintf(outputFile, "%s","Ysre.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->Ysre[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)


	
	sprintf(outputFile, "%s","shifted_fMRI.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->shifted_fMRI[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)



	sprintf(outputFile, "%s","SE.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->SE[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)


	
	sprintf(outputFile, "%s","DELTA.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->DELTA[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)

	
	sprintf(outputFile, "%s","the_SRE_shifted_fMRI.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->the_SRE_shifted_fMRI[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)

	
	sprintf(outputFile, "%s","SE_SRE.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->SE_SRE[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)


	sprintf(outputFile, "%s","X_recomputed.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->X_recomputed[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)

	sprintf(outputFile, "%s","Y_recomputed.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->Y_recomputed[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)


	sprintf(outputFile, "%s","X_recomputed_scaled.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->X_recomputed_scaled[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)

	sprintf(outputFile, "%s","Y_recomputed_scaled.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->Y_recomputed_scaled[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)

	sprintf(outputFile, "%s","ICF.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->ICF[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)

	sprintf(outputFile, "%s","Y.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->Y[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)

	sprintf(outputFile, "%s","X.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->X[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)

		sprintf(outputFile, "%s","Xt.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->Xt[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)
	
	sprintf(outputFile, "%s","TF.img");
	if ((savedata = fopen(outputFile,"wb+"))==NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	} else  { // (save)


	for( int v=0; v < this->n1; v++ ) { // (a)

		for( int f=0; f < this->n2; f++ ) 
	
		fwrite(&pointer->TF[v][f],sizeof(double),1,savedata);

	} // (a)

	fclose(savedata);

	} // (save)


} // saveImages



int main ( int argc, char * argv[] ) {

	char outputFile[128]="SRE2D2017.log";

	FILE * savedata;

	double MAX = 5000000000000000000.0;

if (argc < 11) { std::cout << endl;
				 std::cout << "Please type the image file name" << endl;
				 std::cout << "Please make sure that the image format is Analyze 'double': 64 bits real" << endl;
				 std::cout << "Before running the program, please make sure that the image is padded of 'n >= 1'";
				 std::cout << "number of pixels along X and Y" << endl;
				 std::cout << "Please enter the number of pixels along the X direction (integer)" << endl;
				 std::cout << "Please enter the number of pixels along the Y direction (integer)" << endl;
				 std::cout << "Please enter the pixel size along the X direction (double)" << endl;
				 std::cout << "Please enter the pixel size along the Y direction (double)" << endl;
				 std::cout << "Please enter the misplacement along the X direction (double)" << endl;
				 std::cout << "Please enter the misplacement along the Y direction (double)" << endl;
				 std::cout << "Please enter the XY rotation angle (double)" << endl;
				 std::cout << "Please enter that 'n >= 1' number of pixels along X and Y which will pad the image" << endl;
				 std::cout << "Some data will be lost if you enter a value of n which is greater than" << endl;
				 std::cout << "the actual number of pixels along X and Y which was used to pad the image" << endl;
				 std::cout << "before running the program." << endl;
				 std::cout << "Please type 'n' to scale the Image Data " << endl;
				 std::cout << "or Please type 'r' to use the raw Image Data" << endl;
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

	double x_misplacement_X = atof(argv[6]);
	double y_misplacement_Y = atof(argv[7]);

	double theta = atof(argv[8]);

	char imageFileName[128];
	
	sprintf(imageFileName, "%s", argv[1]);

	int PAD = atoi(argv[9]);

	unsigned char Fyn = 'n';

	Fyn = *argv[10];

	if ( PAD < 1 ) { // if test PAD
	
		std::cout << "Please make sure to pad the image with 'n >= 1' number of pixels along X and Y" << endl;
	
		fprintf(savedata,"%s\n", "Please make sure to pad the image with 'n >= 1' number of pixels along X and Y");

		fclose(savedata);
	
		exit(0);
	
	} // if test PAD
	
	

	std::cout << endl;
	std::cout << "The number of pixels along the X direction is: " << atoi(argv[2]) << endl;
	std::cout << "The number of pixels along the Y direction is: " << atoi(argv[3]) << endl;
	std::cout << "The pixel size along the X direction is: " << atof(argv[4]) << endl;
	std::cout << "The pixel size along the Y direction is: " << atof(argv[5]) << endl;
	std::cout << "The XY rotation angle is: " << atof(argv[8]) << endl;
	std::cout << "The 'n>2' number of pixels along X and Y which you entered to pad the image is: " << atoi(argv[9]) << endl;
	std::cout << "Some data will be lost if you enter a value of n which is greater than" << endl;
	std::cout << "the actual number of pixels along X and Y which was used to pad the image" << endl;
	std::cout << "before running the program." << endl;
	

	
	if ( tolower(Fyn) == 'n' ) 
	std::cout << "The program scales the Image Data before processing: " << Fyn << endl;
	else if ( tolower(Fyn) == 'r' ) 
	std::cout << "The program uses the raw image data: " << Fyn << endl;
	std::cout << endl;

	
	fprintf(savedata,"%s%d\n", "The number of pixels along the X direction is: ", n1);
	fprintf(savedata,"%s%d\n", "The number of pixels along the Y direction is: ", n2);
	fprintf(savedata,"%s%lf\n", "The pixel size along the X direction is: ", XPixelSize);
	fprintf(savedata,"%s%lf\n", "The pixel size along the Y direction is: ", YPixelSize);
	fprintf(savedata,"%s%lf\n", "The XY rotation angle is: ", theta);
	fprintf(savedata,"%s%d\n", "The 'n' number of pixels along X and Y which you entered to pad the image is: ", PAD);
	fprintf(savedata,"%s\n", "Some data will be lost if you enter a value of n which is greater than");
	fprintf(savedata,"%s\n", "the actual number of pixels along X and Y which was used to pad the image");
	fprintf(savedata,"%s\n", "before running the program.");


	if ( tolower(Fyn) == 'n' )
	fprintf(savedata,"%s%c\n", "The program scales the Image Data before processing: ", Fyn);
	else if ( tolower(Fyn) == 'r' )
	fprintf(savedata,"%s%c\n", "The program uses the raw Image Data: ", Fyn);
	fprintf(savedata,"\n");


    double misplacement_X = ((double)1.0 - ( cos( (double)theta ) + sin( (double)theta ) ) + x_misplacement_X);
    double misplacement_Y = ((double)1.0 - ( -sin( (double)theta ) + cos( (double)theta ) ) + y_misplacement_Y);

      misplacement_X = ((double)misplacement_X/XPixelSize);
      misplacement_Y = ((double)misplacement_Y/YPixelSize);

	  //////////////////***********//////////////////////
	  // Above formula scales the misplacement to the  //
	  // pixel size the same way the following formula //
	  // would do: (min - misplacement)/(min - max)    //  
	  //////////////////***********//////////////////////


	SRE2D2013 SRE(n1,n2);

	SRE.allocateData();

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
		
		SRE.pointer->fMRI[i1][i2] = (double)number;

		SRE.pointer->scaledfMRI[i1][i2] = (double)number;
                          
		} // y dim
        
	}  // x dim 

      	
    fclose (pf);


	} // else 
	/// read image file (end)

	std::cout << "Image data loaded" << endl;

	double max=-MAX;
	double min=MAX;

	// make decision as to if to use scaled Image data or Raw Image data (begins)
	if ( tolower(Fyn) == 'n' )
	{  

	/// compute max and min of data (begin)
	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim
	
		if( SRE.pointer->fMRI[i1][i2] > (double)max ) 
			
			max = (double)SRE.pointer->fMRI[i1][i2];
              
		if( SRE.pointer->fMRI[i1][i2] < (double)min ) 
			
			min = (double)SRE.pointer->fMRI[i1][i2];
		

		} // y dim
        
	}  // x dim
	/// compute max and min of data (end)

	// scale (begin)
	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

		

           if ( max == min ) SRE.pointer->scaledfMRI[i1][i2] = (double)0.0;

           else SRE.pointer->scaledfMRI[i1][i2] = (double) NSCALE * (min - SRE.pointer->fMRI[i1][i2]) / (min - max) ;
       


		} // y dim
        
	}  // x dim 
	
	// scale (end)
	std::cout << "Image data scaled" << endl;

	} else if ( tolower(Fyn) == 'r' ) { }
    // make decision as to if to use scaled Image data or Raw Image data


    // compute XSRE and YSRE (begin)
	double omega;
	int XNEI = 1;

	for (int i1=0; i1 < n1-1; i1++) {// x dim

	    for (int i2=0; i2 < n2-1; i2++) { // y dim


		omega = ((double) SRE.pointer->scaledfMRI[i1+1][i2+1] + SRE.pointer->scaledfMRI[i1][i2] - 
		                  SRE.pointer->scaledfMRI[i1+1][i2] - SRE.pointer->scaledfMRI[i1][i2+1] );
        

		 if ( ((double)SRE.pointer->scaledfMRI[i1][i2+1] - SRE.pointer->scaledfMRI[i1][i2] ) == 0.0 && (double)omega != 0.0 ) 

			 SRE.pointer->Xsre[i1][i2] = (double)0.0;
		 

		 else if ( ((double)SRE.pointer->scaledfMRI[i1][i2+1] - SRE.pointer->scaledfMRI[i1][i2] ) != 0.0 && (double)omega == 0.0 ) 

			 SRE.pointer->Xsre[i1][i2] = (double)0.0;

		 
		 else if ( ((double)SRE.pointer->scaledfMRI[i1][i2+1] - SRE.pointer->scaledfMRI[i1][i2] ) != 0.0 && (double)omega != 0.0 ) 

			 SRE.pointer->Xsre[i1][i2] = ((double) -2.0 * (SRE.pointer->scaledfMRI[i1][i2+1] - SRE.pointer->scaledfMRI[i1][i2] ) / omega); 

		
		 else if ( ((double)SRE.pointer->scaledfMRI[i1][i2+1] - SRE.pointer->scaledfMRI[i1][i2] ) == 0.0 && (double)omega == 0.0 ) 

			 SRE.pointer->Xsre[i1][i2] = (double)1.0; // de L'Hopital
		 

		 
		 if ( ((double)SRE.pointer->scaledfMRI[i1+1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) == 0.0 && (double)omega != 0.0 ) 

			 SRE.pointer->Ysre[i1][i2] = (double)0.0;
		 
		 
		 else if ( ((double)SRE.pointer->scaledfMRI[i1+1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) != 0.0 && (double)omega == 0.0 ) 

			 SRE.pointer->Ysre[i1][i2] = (double)0.0;
		
		 
		 else if ( ((double)SRE.pointer->scaledfMRI[i1+1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) != 0.0 && (double)omega != 0.0 ) 

             SRE.pointer->Ysre[i1][i2] = ((double) -2.0 * (SRE.pointer->scaledfMRI[i1+1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) / omega); 


		 else if ( ((double)SRE.pointer->scaledfMRI[i1+1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) == 0.0 && (double)omega == 0.0 ) 

			 SRE.pointer->Ysre[i1][i2] = (double)1.0; // de L'Hopital

		          
    /// calculate last horizontal/vertical stripe of signal (begin)   
	if ( i1 >= 1 && i2 == ((int)n1 - PAD - XNEI) )
	{ // if


		omega = ((double) SRE.pointer->scaledfMRI[i1-1][i2-1] + SRE.pointer->scaledfMRI[i1][i2] - 
		                  SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2-1] );
 
		
		 if ( ((double)SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] ) == 0.0 && (double)omega != 0.0 ) 

			 SRE.pointer->Xsre[i1][i2] = (double)0.0;
		 

		 else if ( ((double)SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] ) != 0.0 && (double)omega == 0.0 ) 

			 SRE.pointer->Xsre[i1][i2] = (double)0.0;

		 
		 else if ( ((double)SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] ) != 0.0 && (double)omega != 0.0 ) 

			 SRE.pointer->Xsre[i1][i2] = ((double) -2.0 * (SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] ) / omega); 

		
		 else if ( ((double)SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] ) == 0.0 && (double)omega == 0.0 ) 

			 SRE.pointer->Xsre[i1][i2] = (double)1.0; // de L'Hopital
		 

		 
		 if ( ((double)SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) == 0.0 && (double)omega != 0.0 ) 

			 SRE.pointer->Ysre[i1][i2] = (double)0.0;
		 
		 
		 else if ( ((double)SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) != 0.0 && (double)omega == 0.0 ) 

			 SRE.pointer->Ysre[i1][i2] = (double)0.0;
		
		 
		 else if ( ((double)SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) != 0.0 && (double)omega != 0.0 ) 

             SRE.pointer->Ysre[i1][i2] = ((double) -2.0 * (SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) / omega); 


		 else if ( ((double)SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) == 0.0 && (double)omega == 0.0 ) 

			 SRE.pointer->Ysre[i1][i2] = (double)1.0; // de L'Hopital


	} // if
	if ( i1 == ((int)n1 - PAD - XNEI) && i2 >= 1 )
	{ // if

		omega = ((double) SRE.pointer->scaledfMRI[i1-1][i2-1] + SRE.pointer->scaledfMRI[i1][i2] - 
		                  SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2-1] );
 
		
		 if ( ((double)SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] ) == 0.0 && (double)omega != 0.0 ) 

			 SRE.pointer->Xsre[i1][i2] = (double)0.0;
		 

		 else if ( ((double)SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] ) != 0.0 && (double)omega == 0.0 ) 

			 SRE.pointer->Xsre[i1][i2] = (double)0.0;

		 
		 else if ( ((double)SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] ) != 0.0 && (double)omega != 0.0 ) 

			 SRE.pointer->Xsre[i1][i2] = ((double) -2.0 * (SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] ) / omega); 

		
		 else if ( ((double)SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] ) == 0.0 && (double)omega == 0.0 ) 

			 SRE.pointer->Xsre[i1][i2] = (double)1.0; // de L'Hopital
		 

		 
		 if ( ((double)SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) == 0.0 && (double)omega != 0.0 ) 

			 SRE.pointer->Ysre[i1][i2] = (double)0.0;
		 
		 
		 else if ( ((double)SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) != 0.0 && (double)omega == 0.0 ) 

			 SRE.pointer->Ysre[i1][i2] = (double)0.0;
		
		 
		 else if ( ((double)SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) != 0.0 && (double)omega != 0.0 ) 

             SRE.pointer->Ysre[i1][i2] = ((double) -2.0 * (SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) / omega); 


		 else if ( ((double)SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) == 0.0 && (double)omega == 0.0 ) 

			 SRE.pointer->Ysre[i1][i2] = (double)1.0; // de L'Hopital
 

	} // if
	/// calculate last vertical stripe of signal (end)   


		} // y dim
        
	}  // x dim
	   	
	// calculate SRE (end)
    std::cout << "XSRE and YSRE calculated" << endl;

	// scale X_sre (begin)
	max=-MAX;
	min=MAX;

	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim
	
		if( SRE.pointer->Xsre[i1][i2] > (double)max ) max = (double)SRE.pointer->Xsre[i1][i2];
              
		if( SRE.pointer->Xsre[i1][i2] < (double)min ) min = (double)SRE.pointer->Xsre[i1][i2];
		

		} // y dim
        
	}  // x dim

	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim


           if ( max == min ) SRE.pointer->Xsre[i1][i2] = (double)0.0;

           else SRE.pointer->Xsre[i1][i2] = (double) misplacement_X * (min - SRE.pointer->Xsre[i1][i2]) / (min - max) ;
              

		} // y dim
        
	}  // x dim
	// scale X_sre (end)

	// scale Y_sre (begin)
	max=-MAX;
	min=MAX;

	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim


		if( SRE.pointer->Ysre[i1][i2] > (double)max ) max = (double)SRE.pointer->Ysre[i1][i2];
              
		if( SRE.pointer->Ysre[i1][i2] < (double)min ) min = (double)SRE.pointer->Ysre[i1][i2];
		

		} // y dim
        
	}  // x dim

	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim
  

           if ( max == min ) SRE.pointer->Ysre[i1][i2] = (double)0.0;

           else SRE.pointer->Ysre[i1][i2] = (double) misplacement_Y * (min - SRE.pointer->Ysre[i1][i2]) / (min - max) ;
                

		} // y dim
        
	}  // x dim
	
   // scale Y_sre (end)

	// shift the image of the given misplacement (begin)
	for (int i1=0; i1 < n1-1; i1++) {// x dim

	    for (int i2=0; i2 < n2-1; i2++) { // y dim

		
           
		SRE.pointer->shifted_fMRI[i1][i2] = (double) SRE.pointer->fMRI[i1][i2]  + 
		
		misplacement_X * ( SRE.pointer->scaledfMRI[i1+1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) + 
		
		misplacement_Y * ( SRE.pointer->scaledfMRI[i1][i2+1] - SRE.pointer->scaledfMRI[i1][i2] )  + 
		
		misplacement_X * misplacement_Y * ( SRE.pointer->scaledfMRI[i1+1][i2+1] + SRE.pointer->scaledfMRI[i1][i2] - 
		                                    SRE.pointer->scaledfMRI[i1+1][i2] - SRE.pointer->scaledfMRI[i1][i2+1] ) ;

		
	/// calculate last horizontal/vertical stripe of signal (begin)   
	if ( i1 >= 1 && i2 == ((int)n1 - PAD - XNEI) )
	{ // if

	
	    SRE.pointer->shifted_fMRI[i1][i2] = (double) SRE.pointer->fMRI[i1][i2]  + 
		
		misplacement_X * ( SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) + 
		
		misplacement_Y * ( SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] )  + 
		
		misplacement_X * misplacement_Y * ( SRE.pointer->scaledfMRI[i1-1][i2-1] + SRE.pointer->scaledfMRI[i1][i2] - 
		                                    SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2-1] ) ;


	} // if
	if ( i1 == ((int)n1 - PAD - XNEI) && i2 >= 1 )
	{ // if

	
		SRE.pointer->shifted_fMRI[i1][i2] = (double) SRE.pointer->fMRI[i1][i2]  + 
		
		misplacement_X * ( SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) + 
		
		misplacement_Y * ( SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] )  + 
		
		misplacement_X * misplacement_Y * ( SRE.pointer->scaledfMRI[i1-1][i2-1] + SRE.pointer->scaledfMRI[i1][i2] - 
		                                    SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2-1] ) ;

	} // if
	/// calculate last vertical stripe of signal (end)   
	

 		} // y dim
        
	}  // x dim

	// shift the image of the given misplacement (end)
	std::cout << "Image data shifted" << endl;

	// compute SE (begin)
	double SE_sum = 0.0;
	long int counter = 0;
	
	for (int i1=0; i1 < n1; i1++) {// x dim

		for (int i2=0; i2 < n2; i2++) { // y dim


		counter++;

		SRE.pointer->SE[i1][i2] = (double) sqrt( ( SRE.pointer->fMRI[i1][i2] - SRE.pointer->shifted_fMRI[i1][i2] ) * 
			                                     ( SRE.pointer->fMRI[i1][i2] - SRE.pointer->shifted_fMRI[i1][i2] ) );  

		SE_sum = SRE.pointer->SE[i1][i2] + SE_sum;


		} // y dim
        
	}  // x dim	

	// compute SE (end)

	std::cout << "SE with no SRE is: " << ((double)SE_sum / (counter))  << endl;
	std::cout << endl;

	fprintf(savedata,"%s%e\n", "SE with no SRE is: ", ((double)SE_sum / (counter)) );
	fprintf(savedata,"\n");


	/// compute DELTA and recomputed_X and recomputed_Y (begin)  
	double k, s;

	for (int i1=0; i1 < n1-1; i1++) {// x dim

	    for (int i2=0; i2 < n2-1; i2++) { // y dim

	   
        k = (double) SRE.pointer->fMRI[i1][i2] * SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] + 
				   ( SRE.pointer->Xsre[i1][i2] * SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] / 2.0 ) * 
				   ( SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->fMRI[i1][i2] ) + 
				   ( SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] * SRE.pointer->Ysre[i1][i2] / 2.0 ) * 
				   ( SRE.pointer->fMRI[i1][i2+1] - SRE.pointer->fMRI[i1][i2] )  + 
				   ( SRE.pointer->Xsre[i1][i2] * SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] * SRE.pointer->Ysre[i1][i2] / 4.0 ) * 
				   ( SRE.pointer->fMRI[i1+1][i2+1] + SRE.pointer->fMRI[i1][i2] - SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->fMRI[i1][i2+1] ) ; 

        s = (double) SRE.pointer->fMRI[i1][i2] * ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) ) + 
				 ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * 
				   ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) / 2.0 ) * ( SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->fMRI[i1][i2] ) + 
				 ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * 
				   ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) / 2.0 ) * ( SRE.pointer->fMRI[i1][i2+1] - SRE.pointer->fMRI[i1][i2] ) + 
				 ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * 
				   ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) / 4.0 ) * 
				   ( SRE.pointer->fMRI[i1+1][i2+1] + SRE.pointer->fMRI[i1][i2] - SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->fMRI[i1][i2+1] ) ; 
       

	/// calculate last horizontal/vertical stripe of signal (begin)   
	if ( i1 >= 1 && i2 == ((int)n1 - PAD - XNEI) )
	{ // if

		
		k = (double) SRE.pointer->fMRI[i1][i2] * SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] + 
				   ( SRE.pointer->Xsre[i1][i2] * SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] / 2.0 ) * 
				   ( SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2] ) + 
				   ( SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] * SRE.pointer->Ysre[i1][i2] / 2.0 ) * 
				   ( SRE.pointer->fMRI[i1][i2-1] - SRE.pointer->fMRI[i1][i2] )  + 
				   ( SRE.pointer->Xsre[i1][i2] * SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] * SRE.pointer->Ysre[i1][i2] / 4.0 ) * 
				   ( SRE.pointer->fMRI[i1-1][i2-1] + SRE.pointer->fMRI[i1][i2] - SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2-1] ) ; 

        s = (double) SRE.pointer->fMRI[i1][i2] * ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) ) + 
				 ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * 
				   ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) / 2.0 ) * ( SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2] ) + 
				 ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * 
				   ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) / 2.0 ) * ( SRE.pointer->fMRI[i1][i2-1] - SRE.pointer->fMRI[i1][i2] ) + 
				 ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * 
				   ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) / 4.0 ) * 
				   ( SRE.pointer->fMRI[i1-1][i2-1] + SRE.pointer->fMRI[i1][i2] - SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2-1] ) ; 
     

	} // if
	if ( i1 == ((int)n1 - PAD - XNEI) && i2 >= 1 )
	{ // if

	
	    k = (double) SRE.pointer->fMRI[i1][i2] * SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] + 
				   ( SRE.pointer->Xsre[i1][i2] * SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] / 2.0 ) * 
				   ( SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2] ) + 
				   ( SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] * SRE.pointer->Ysre[i1][i2] / 2.0 ) * 
				   ( SRE.pointer->fMRI[i1][i2-1] - SRE.pointer->fMRI[i1][i2] )  + 
				   ( SRE.pointer->Xsre[i1][i2] * SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] * SRE.pointer->Ysre[i1][i2] / 4.0 ) * 
				   ( SRE.pointer->fMRI[i1-1][i2-1] + SRE.pointer->fMRI[i1][i2] - SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2-1] ) ; 

        s = (double) SRE.pointer->fMRI[i1][i2] * ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) ) + 
				 ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * 
				   ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) / 2.0 ) * ( SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2] ) + 
				 ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * 
				   ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) / 2.0 ) * ( SRE.pointer->fMRI[i1][i2-1] - SRE.pointer->fMRI[i1][i2] ) + 
				 ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * 
				   ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) / 4.0 ) * 
				   ( SRE.pointer->fMRI[i1-1][i2-1] + SRE.pointer->fMRI[i1][i2] - SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2-1] ) ; 
     
	} // if
	/// calculate last vertical stripe of signal (end) 


		   if ( (double)s == 0.0 && (double)k == 0.0 ) SRE.pointer->DELTA[i1][i2] = (double)1.0; // de l'Hopital
           
		   else if ( (double)s == 0.0 && (double)k != 0.0 ) SRE.pointer->DELTA[i1][i2] = (double)0.0;
		   
		   else if ( (double)s != 0.0 && (double)k == 0.0 ) SRE.pointer->DELTA[i1][i2] = (double)0.0;

		   else  if ( (double)s != 0.0 && (double)k != 0.0 ) SRE.pointer->DELTA[i1][i2] = (double)s/k;
           

 		} // y dim
        
	}  // x dim

    // compute DELTA (end)
	std::cout << "DELTA calculated" << endl;

	// calculate ICF (begin)
	std::cout << "Compute Intensity-Curvature Functional" << endl;
	
	for (int i1=0; i1 < n1-1; i1++) {// x dim

	    for (int i2=0; i2 < n2-1; i2++) { // y dim


			SRE.pointer->X[i1][i2] = (double)SRE.pointer->fMRI[i1][i2];
	 
			SRE.pointer->Y[i1][i2] = (double)SRE.pointer->fMRI[i1][i2];


		} // y dim
	} // x dim
	

	for (int i1=0; i1 < n1-1; i1++) {// x dim

	    for (int i2=0; i2 < n2-1; i2++) { // y dim

		   
        k = (double) SRE.pointer->fMRI[i1][i2] * misplacement_X * misplacement_Y + 
				   ( misplacement_X * misplacement_Y * misplacement_X / 2.0) * 
				   ( SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->fMRI[i1][i2] ) + 
				   ( misplacement_X * misplacement_Y * misplacement_Y / 2.0) * 
				   ( SRE.pointer->fMRI[i1][i2+1] - SRE.pointer->fMRI[i1][i2] ) +
				   ( misplacement_X * misplacement_X * misplacement_Y * misplacement_Y / 4.0) * 
				   ( SRE.pointer->fMRI[i1+1][i2+1] + SRE.pointer->fMRI[i1][i2] - SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->fMRI[i1][i2+1] );

				   
        s = (double) SRE.pointer->fMRI[i1][i2] * misplacement_X * misplacement_Y; 
       
		   if ( (double)s == 0.0 && (double)k == 0.0 ) SRE.pointer->ICF[i1][i2] = (double)1.0; // de l'Hopital
           
		   else if ( (double)s == 0.0 && (double)k != 0.0 ) SRE.pointer->ICF[i1][i2] = (double)0.0;
		   
		   else if ( (double)s != 0.0 && (double)k == 0.0 ) SRE.pointer->ICF[i1][i2] = (double)0.0;

		   else  if ( (double)s != 0.0 && (double)k != 0.0 ) SRE.pointer->ICF[i1][i2] = (double)s/k;

		    /* 02-09-2017 */
		   /// calculation of the the input function: X, 
		   /// the output function: Y, and the transfer function: TF (begins)
		    SRE.pointer->Y[i1][i2] = ( (double) misplacement_X  * misplacement_Y  * SRE.pointer->X[i1][i2] ) /
			                         ( (double) misplacement_X  * misplacement_Y  * SRE.pointer->X[i1][i2] +
									   (double) misplacement_X  * misplacement_X  * misplacement_Y  * 
									  ((double) (SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->X[i1][i2]) / 2.0) +
									   (double) misplacement_X  * misplacement_Y  * misplacement_Y  * 
									  ((double) (SRE.pointer->fMRI[i1][i2+1] - SRE.pointer->X[i1][i2]) / 2.0) +
									 ( (double) misplacement_X  * misplacement_Y  * misplacement_X  * misplacement_Y  *
									 ( (double)SRE.pointer->X[i1][i2] + SRE.pointer->fMRI[i1+1][i2+1] - SRE.pointer->fMRI[i1+1][i2] - 
													 SRE.pointer->fMRI[i1][i2+1]) / 4.0) );

		    SRE.pointer->X[i1][i2] = ( ((double) misplacement_X  * SRE.pointer->fMRI[i1+1][i2] / 2.0) +
									   ((double) misplacement_Y  * SRE.pointer->fMRI[i1][i2+1] / 2.0) + 
									    (double) misplacement_X  * misplacement_Y * 
									   ((double) SRE.pointer->fMRI[i1+1][i2+1] - SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->fMRI[i1][i2+1] / 4.0) ) *
									    (double) SRE.pointer->Y[i1][i2] /
								   	 (  (double) 1.0 - ( (double) SRE.pointer->Y[i1][i2] *
			                          ( (double) 1.0 - misplacement_X / 2.0 - (double) misplacement_Y / 2.0 
									  + (double) misplacement_X  * misplacement_Y / 4.0 ) ) );

			  SRE.pointer->Xt[i1][i2] = (double) SRE.pointer->fMRI[i1][i2];

		 if ( SRE.pointer->Xt[i1][i2] != (double) 0.0 )

			  SRE.pointer->TF[i1][i2] = ((double) SRE.pointer->Y[i1][i2] / SRE.pointer->Xt[i1][i2]);
		 
		 else SRE.pointer->TF[i1][i2] = (double) 0.0;
		 /// calculation of the the input function: X, 
		/// the output function: Y, and the transfer function: TF (ends)
		   /* 02-09-2017 */

		} // y dim
        
	}  // x dim


	std::cout << "Intensity-Curvature Functional Calculated" << endl;
	// calculate ICF(end)

	// recomputed_X and recomputed_Y (begin)
	double a, p, t, nx, ny, qx, qy;

	for (int i1=0; i1 < n1-1; i1++) {// x dim

	    for (int i2=0; i2 < n2-1; i2++) { // y dim


        a = ( (double) SRE.pointer->fMRI[i1+1][i2+1] + SRE.pointer->fMRI[i1][i2] - 
		               SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->fMRI[i1][i2+1] );       

        k = SRE.pointer->fMRI[i1][i2] + ( SRE.pointer->Xsre[i1][i2] * ( SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->fMRI[i1][i2] ) ) + 
		  ( SRE.pointer->Ysre[i1][i2] * ( SRE.pointer->fMRI[i1][i2+1] - SRE.pointer->fMRI[i1][i2] ) )  + 
		  ( SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] * 
		  ( SRE.pointer->fMRI[i1+1][i2+1] + SRE.pointer->fMRI[i1][i2] - SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->fMRI[i1][i2+1] ) ) ;   

		s = (double)SRE.pointer->DELTA[i1][i2];

		p = (double) ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * ( SRE.pointer->fMRI[i1][i2+1] - SRE.pointer->fMRI[i1][i2] ) + SRE.pointer->Xsre[i1][i2] * 
	              (  ( SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->fMRI[i1][i2] ) + ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * a );
   
        t = (double) ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->fMRI[i1][i2] ) + SRE.pointer->Ysre[i1][i2] * 
		          (  ( SRE.pointer->fMRI[i1][i2+1] - SRE.pointer->fMRI[i1][i2] ) + ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * a );    

        nx = ((double) ( k * s ) - SRE.pointer->fMRI[i1][i2] - p);
    
        ny = ((double) ( k * s ) - SRE.pointer->fMRI[i1][i2] - t);

        qx = ( ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * a ) - ( SRE.pointer->fMRI[i1+1][i2] - SRE.pointer->fMRI[i1][i2]  );

        qy = ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * a ) - ( SRE.pointer->fMRI[i1][i2+1] - SRE.pointer->fMRI[i1][i2]  );


		if ( (double)nx == 0.0 && (double)qx == 0.0 ) SRE.pointer->X_recomputed[i1][i2] = (double)1.0; // de l'Hopital

		else if ( (double)nx == 0.0 && (double)qx != 0.0 ) SRE.pointer->X_recomputed[i1][i2] = (double)0.0;

		else if ( (double)nx != 0.0 && (double)qx == 0.0 ) SRE.pointer->X_recomputed[i1][i2] = (double)0.0;
		
		else SRE.pointer->X_recomputed[i1][i2] =  ((double)nx/qx);


		if ( (double)ny == 0.0 && (double)qy == 0.0 ) SRE.pointer->Y_recomputed[i1][i2] = (double)1.0; // de l'Hopital

		else if ( (double)ny == 0.0 && (double)qy != 0.0 ) SRE.pointer->Y_recomputed[i1][i2] = (double)0.0;

		else if ( (double)ny != 0.0 && (double)qy == 0.0 ) SRE.pointer->Y_recomputed[i1][i2] = (double)0.0;
		
		else SRE.pointer->Y_recomputed[i1][i2] =  ((double)ny/qy);


	/// calculate last horizontal/vertical stripe of signal (begin)   
	if ( i1 >= 1 && i2 == ((int)n1 - PAD - XNEI) )
	{ // if
	
	    a = ( (double) SRE.pointer->fMRI[i1-1][i2-1] + SRE.pointer->fMRI[i1][i2] - 
		               SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2-1] );       

        k = SRE.pointer->fMRI[i1][i2] + ( SRE.pointer->Xsre[i1][i2] * ( SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2] ) ) + 
		  ( SRE.pointer->Ysre[i1][i2] * ( SRE.pointer->fMRI[i1][i2-1] - SRE.pointer->fMRI[i1][i2] ) )  + 
		  ( SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] * 
		  ( SRE.pointer->fMRI[i1-1][i2-1] + SRE.pointer->fMRI[i1][i2] - SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2-1] ) ) ;   

		s = (double)SRE.pointer->DELTA[i1][i2];

		p = (double) ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * ( SRE.pointer->fMRI[i1][i2-1] - SRE.pointer->fMRI[i1][i2] ) + SRE.pointer->Xsre[i1][i2] * 
	              (  ( SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2] ) + ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * a );
   
        t = (double) ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2] ) + SRE.pointer->Ysre[i1][i2] * 
		          (  ( SRE.pointer->fMRI[i1][i2-1] - SRE.pointer->fMRI[i1][i2] ) + ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * a );    

        nx = ((double) ( k * s ) - SRE.pointer->fMRI[i1][i2] - p);
    
        ny = ((double) ( k * s ) - SRE.pointer->fMRI[i1][i2] - t);

        qx = ( ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * a ) - ( SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2]  );

        qy = ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * a ) - ( SRE.pointer->fMRI[i1][i2-1] - SRE.pointer->fMRI[i1][i2]  );

  
		if ( (double)nx == 0.0 && (double)qx == 0.0 ) SRE.pointer->X_recomputed[i1][i2] = (double)1.0; // de l'Hopital

		else if ( (double)nx == 0.0 && (double)qx != 0.0 ) SRE.pointer->X_recomputed[i1][i2] = (double)0.0;
		
		else if ( (double)nx != 0.0 && (double)qx == 0.0 ) SRE.pointer->X_recomputed[i1][i2] = (double)0.0;

		else SRE.pointer->X_recomputed[i1][i2] =  ((double)nx/qx);


		if ( (double)ny == 0.0 && (double)qy == 0.0 ) SRE.pointer->Y_recomputed[i1][i2] = (double)1.0; // de l'Hopital

		else if ( (double)ny == 0.0 && (double)qy != 0.0 ) SRE.pointer->Y_recomputed[i1][i2] = (double)0.0;

		else if ( (double)ny != 0.0 && (double)qy == 0.0 ) SRE.pointer->Y_recomputed[i1][i2] = (double)0.0;
		
		else SRE.pointer->Y_recomputed[i1][i2] =  ((double)ny/qy);

	} // if
	if ( i1 == ((int)n1 - PAD - XNEI) && i2 >= 1  )
	{ // if

	    a = ( (double) SRE.pointer->fMRI[i1-1][i2-1] + SRE.pointer->fMRI[i1][i2] - 
		               SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2-1] );       

        k = SRE.pointer->fMRI[i1][i2] + ( SRE.pointer->Xsre[i1][i2] * ( SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2] ) ) + 
		  ( SRE.pointer->Ysre[i1][i2] * ( SRE.pointer->fMRI[i1][i2-1] - SRE.pointer->fMRI[i1][i2] ) )  + 
		  ( SRE.pointer->Xsre[i1][i2] * SRE.pointer->Ysre[i1][i2] * 
		  ( SRE.pointer->fMRI[i1-1][i2-1] + SRE.pointer->fMRI[i1][i2] - SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2-1] ) ) ;   

		s = (double)SRE.pointer->DELTA[i1][i2];

		p = (double) ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * ( SRE.pointer->fMRI[i1][i2-1] - SRE.pointer->fMRI[i1][i2] ) + SRE.pointer->Xsre[i1][i2] * 
	              (  ( SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2] ) + ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * a );
   
        t = (double) ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * ( SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2] ) + SRE.pointer->Ysre[i1][i2] * 
		          (  ( SRE.pointer->fMRI[i1][i2-1] - SRE.pointer->fMRI[i1][i2] ) + ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * a );    

        nx = ((double) ( k * s ) - SRE.pointer->fMRI[i1][i2] - p);
    
        ny = ((double) ( k * s ) - SRE.pointer->fMRI[i1][i2] - t);

        qx = ( ( SRE.pointer->Ysre[i1][i2] - misplacement_Y ) * a ) - ( SRE.pointer->fMRI[i1-1][i2] - SRE.pointer->fMRI[i1][i2]  );

        qy = ( ( SRE.pointer->Xsre[i1][i2] - misplacement_X ) * a ) - ( SRE.pointer->fMRI[i1][i2-1] - SRE.pointer->fMRI[i1][i2]  );

				
		if ( (double)nx == 0.0 && (double)qx == 0.0 ) SRE.pointer->X_recomputed[i1][i2] = (double)1.0; // de l'Hopital

		else if ( (double)nx == 0.0 && (double)qx != 0.0 ) SRE.pointer->X_recomputed[i1][i2] = (double)0.0;
		
		else if ( (double)nx != 0.0 && (double)qx == 0.0 ) SRE.pointer->X_recomputed[i1][i2] = (double)0.0;

		else SRE.pointer->X_recomputed[i1][i2] =  ((double)nx/qx);


		if ( (double)ny == 0.0 && (double)qy == 0.0 ) SRE.pointer->Y_recomputed[i1][i2] = (double)1.0; // de l'Hopital

		else if ( (double)ny == 0.0 && (double)qy != 0.0 ) SRE.pointer->Y_recomputed[i1][i2] = (double)0.0;

		else if ( (double)ny != 0.0 && (double)qy == 0.0 ) SRE.pointer->Y_recomputed[i1][i2] = (double)0.0;
		
		else SRE.pointer->Y_recomputed[i1][i2] =  ((double)ny/qy);


	} // if
	/// calculate last vertical stripe of signal (end) 

    
  		} // y dim
        
	}  // x dim

	// recomputed_X and recomputed_Y (end)
   	/// compute DELTA and recomputed_X and recomputed_Y (end)
 
	/// compute max and min values of recomputed locations (begin)
	/// scale the re-computed locations (begin)
	max=-MAX;
	min=MAX;

	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

	
		if( SRE.pointer->X_recomputed[i1][i2] > (double)max ) max = (double)SRE.pointer->X_recomputed[i1][i2];
              
		if( SRE.pointer->X_recomputed[i1][i2] < (double)min ) min = (double)SRE.pointer->X_recomputed[i1][i2];
		

		} // y dim
        
	}  // x dim


	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

	
           if ( max == min ) SRE.pointer->X_recomputed_scaled[i1][i2] = (double)0.0;

           else  SRE.pointer->X_recomputed_scaled[i1][i2] = ((double) ( XPixelSize ) * ( min - SRE.pointer->X_recomputed[i1][i2] ) / ( min - max ));
              

		} // y dim
        
	}  // x dim

	max=-MAX;
	min=MAX;

	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

	
		if( SRE.pointer->Y_recomputed[i1][i2] > (double)max ) max = (double)SRE.pointer->Y_recomputed[i1][i2];
              
		if( SRE.pointer->Y_recomputed[i1][i2] < (double)min ) min = (double)SRE.pointer->Y_recomputed[i1][i2];
		

		} // y dim
        
	}  // x dim


	for (int i1=0; i1 < n1; i1++) {// x dim
       	
		for (int i2=0; i2 < n2; i2++) { // y dim

	
           if ( max == min ) SRE.pointer->Y_recomputed_scaled[i1][i2] = (double)0.0;

           else  SRE.pointer->Y_recomputed_scaled[i1][i2] = ((double) ( YPixelSize ) * ( min - SRE.pointer->Y_recomputed[i1][i2] ) / ( min - max ));
              

		} // y dim
        
	}  // x dim


	/// compute max and min values of recomputed locations (end)
	/// scale the re-computed locations (end)

	std::cout << "Re-computed locations calculated" << endl;

	// shift forward (begin)
	for (int i1=0; i1 < n1-1; i1++) {// x dim

	    for (int i2=0; i2 < n2-1; i2++) { // y dim

           
		SRE.pointer->the_SRE_shifted_fMRI[i1][i2] = (double) SRE.pointer->fMRI[i1][i2]  + 
		
		SRE.pointer->X_recomputed_scaled[i1][i2] * 
		
		( SRE.pointer->scaledfMRI[i1+1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) + 
		
		SRE.pointer->Y_recomputed_scaled[i1][i2] * 
		
		( SRE.pointer->scaledfMRI[i1][i2+1] - SRE.pointer->scaledfMRI[i1][i2] )  + 
		
		SRE.pointer->X_recomputed_scaled[i1][i2] * SRE.pointer->Y_recomputed_scaled[i1][i2] *
		
		( SRE.pointer->scaledfMRI[i1+1][i2+1] + SRE.pointer->scaledfMRI[i1][i2] - 
		  SRE.pointer->scaledfMRI[i1+1][i2] - SRE.pointer->scaledfMRI[i1][i2+1] ) ;

		/// calculate last horizontal/vertical stripe of signal (begin)   
		if ( i1 >= 1 && i2 == ((int)n1 - PAD - XNEI) )
		{ // if

	
		SRE.pointer->the_SRE_shifted_fMRI[i1][i2] = (double) SRE.pointer->fMRI[i1][i2]  + 
		
		SRE.pointer->X_recomputed_scaled[i1][i2] * 
		
		( SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) + 
		
		SRE.pointer->Y_recomputed_scaled[i1][i2] * 
		
		( SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] )  + 
		
		SRE.pointer->X_recomputed_scaled[i1][i2] * SRE.pointer->Y_recomputed_scaled[i1][i2] *
		
		( SRE.pointer->scaledfMRI[i1-1][i2-1] + SRE.pointer->scaledfMRI[i1][i2] - 
		  SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2-1] ) ;

		} // if
		if ( i1 == ((int)n1 - PAD - XNEI) && i2 >= 1 )
		{ // if

	
		SRE.pointer->the_SRE_shifted_fMRI[i1][i2] = (double) SRE.pointer->fMRI[i1][i2]  + 
		
		SRE.pointer->X_recomputed_scaled[i1][i2] * 
		
		( SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2] ) + 
		
		SRE.pointer->Y_recomputed_scaled[i1][i2] * 
		
		( SRE.pointer->scaledfMRI[i1][i2-1] - SRE.pointer->scaledfMRI[i1][i2] )  + 
		
		SRE.pointer->X_recomputed_scaled[i1][i2] * SRE.pointer->Y_recomputed_scaled[i1][i2] *
		
		( SRE.pointer->scaledfMRI[i1-1][i2-1] + SRE.pointer->scaledfMRI[i1][i2] - 
		  SRE.pointer->scaledfMRI[i1-1][i2] - SRE.pointer->scaledfMRI[i1][i2-1] ) ;

		} // if
		/// calculate last vertical stripe of signal (end)    

 		} // y dim
        
	}  // x dim
	// shift forward (end)

	std::cout << "Image data SRE shifted" << endl;

	// compute SE_SRE (begin)
	double SE_SRE_sum = 0.0;
	counter = 0;

	for (int i1=0; i1 < n1; i1++) {// x dim

		for (int i2=0; i2 < n2; i2++) { // y dim


		counter++;

		SRE.pointer->SE_SRE[i1][i2] = (double) sqrt( ( SRE.pointer->fMRI[i1][i2] - SRE.pointer->the_SRE_shifted_fMRI[i1][i2] ) * 
			                                         ( SRE.pointer->fMRI[i1][i2] - SRE.pointer->the_SRE_shifted_fMRI[i1][i2] ) );  

		SE_SRE_sum = SRE.pointer->SE_SRE[i1][i2] + SE_SRE_sum;



		} // y dim
        
	}  // x dim

	// compute SE_SRE (end)

	std::cout << "SE with SRE is: " << ((double)SE_SRE_sum / (counter))  << endl;
	std::cout << endl;

	fprintf(savedata,"%s%e\n", "SE with SRE is: ", ((double)SE_SRE_sum / (counter)) );
	fprintf(savedata,"\n");

	
	SRE.save();

	std::cout << "End of Computation..." << endl;
	std::cout << endl;

	fprintf(savedata,"%s\n", "End of Computation...");
	fprintf(savedata,"\n");

	fclose(savedata);
	delete SRE.pointer;
	SRE.~SRE2D2013();
	} // processing (end)

	} // run the program (end)

	system("java processCompleted");
	
	return 0;
} // end of main 
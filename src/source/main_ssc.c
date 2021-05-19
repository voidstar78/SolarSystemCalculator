
/*

Author: STEVE LEWIS - 2021  PROVIDED FOR PUBLIC DOMAIN USE

contact.steve.usa@gmail.com

I am trusting that information at the following article is correct:

https://www.universetoday.com/15462/how-far-are-the-planets-from-the-sun/

From which, is summarized the following data:

             milKM milMI AU
Mercury      46    29    0.307   CLOSEST
             70    43    0.466   FARTHEST
						 57    35    0.387   AVERAGE
						 
Venus        107   66    0.718
             109   68    0.728
						 108   67    0.722
						 
Earth        147   91    0.980
             152   94    1.010
						 150   93    1.000
						 
Mars         205   127   1.380
             249   155   1.660
						 228   142   1.520
						 
Jupiter      741   460   4.950
             817   508   5.460
						 779   484   5.200						
						 
Saturn       1350  839   9.050
             1510  938   10.12
						 1430  889   9.580
						 
Uranus       2750  1710  18.40
             3000  1860  20.10
						 2880  1790  19.20
						 
Neptune      4450  2770  29.80
             4550  2830  30.40
						 4500  2800  30.10
						 						 
Pluto        4440  2760  29.70
             7380  4590  49.30
						 5910  3670  39.50
						 
						 
SAMPLE OUTPUT:
					 
1234567890123456789012345678901234567890
        NEAREST   FARTHEST  AVERAGE   
Mercury 006'003"  009'004"  007'007"  
 mKM/mMi 0046/0029 0070/0043 0057/0035 
 AU      00000.307 00000.466 00000.387 
Venus   014'004"  014'009"  014'007"  
 mKM/mMi 0107/0066 0109/0068 0108/0067 
 AU      00000.718 00000.728 00000.722 
Earth   019'009"  020'005"  020'003"  
 mKM/mMi 0147/0091 0152/0094 0150/0093 
 AU      00000.980 00001.010 00001.000 
Mars    027'008"  033'009"  030'011"  
 mKM/mMi 0205/0127 0249/0155 0228/0142 
 AU      00001.380 00001.660 00001.520 
Jupiter 100'002"  110'008"  105'005"  
 mKM/mMi 0741/0460 0817/0508 0779/0484 
 AU      00004.950 00005.460 00005.200 
Saturn  182'009"  204'004"  193'008"  
 mKM/mMi 1350/0839 1510/0938 1430/0889 
 AU      00009.050 00010.120 00009.580 
Uranus  372'006"  405'002"  389'011"  
 mKM/mMi 2750/1710 3000/1860 2880/1790 
 AU      00018.400 00020.100 00019.200 
Neptune 603'005"  616'006"  610'000"  
 mKM/mMi 4450/2770 4450/2830 4500/2800 
 AU      00029.800 00030.400 00030.100 
Pluto   601'003"  1000'000"  799'006"  
 mKM/mMi 4440/2760 7380/4590 5910/3670 
 AU      00029.700 00049.300 00039.500 					 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USE_GETS           //< Enable to use gets(xxx) versus getline(xxx)
#define ABBREVIATED_MODE   //< Enable to skip repeating the reference data

#define TRUE 1
#define FALSE 0

//#define SSC_TEST_MODE  //< Enable this for quick testing of cases without prompting for any input

#define NUM_PLANETS 9
char planet_names[NUM_PLANETS][8] = {
	{"mercury\0"},
	{"venus\0"},
	{"earth\0"},
	{"mars\0"},
	{"jupiter\0"},
	{"saturn\0"},
	{"uranus\0"},
	{"neptune\0"},
	{"pluto\0"}
};

#define INDEX_NEAREST  0
#define INDEX_FARTHEST 1
#define INDEX_AVERAGE  2

#define INDEX_MIL_KM   0  // Millions of KM
#define INDEX_MIL_MI   1  // Millions of Miles
#define INDEX_AU       2  // Astronomical Unit  (Sun to Earth distance)

float planet_distance_data[9*3][3] = {
// MERCURY
	{46.0f,    29.0f,    0.307f},  // NEAREST
	{70.0f,    43.0f,    0.466f},  // FARTHEST
	{57.0f,    35.0f,    0.387f},  // AVERAGE
// VENUS
  {107.0f,   66.0f,    0.718f},
	{109.0f,   68.0f,    0.728f},
	{108.0f,   67.0f,    0.722f},
// EARTH						 
  {147.0f,   91.0f,    0.980f},
	{152.0f,   94.0f,    1.010f},
	{150.0f,   93.0f,    1.000f},
// MARS						 
  {205.0f,   127.0f,   1.380f},
	{249.0f,   155.0f,   1.660f},
	{228.0f,   142.0f,   1.520f},
// JUPITER						 
  {741.0f,   460.0f,   4.950f},
	{817.0f,   508.0f,   5.460f},
	{779.0f,   484.0f,   5.200f},
// SATURN						 
  {1350.0f,  839.0f,   9.05f},
	{1510.0f,  938.0f,   10.12f},
	{1430.0f,  889.0f,   9.58f},
// URANUS						 
  {2750.0f,  1710.0f,  18.4f},
	{3000.0f,  1860.0f,  20.1f},
	{2880.0f,  1790.0f,  19.2f},
// NEPTUNE						 
  {4450.0f,  2770.0f,  29.8f},
	{4550.0f,  2830.0f,  30.4f},
	{4500.0f,  2800.0f,  30.1f},
// PLUTO
  {4440.0f,  2760.0f,  29.7f},
	{7380.0f,  4590.0f,  49.3f},
	{5910.0f,  3670.0f,  39.5f}
};		

#define DEFAULT_WORK_DISTANCE_FT    50.0f
#define DISTANCE_TYPE_NONE          0
#define DISTANCE_TYPE_NEAREST_MASK  1
#define DISTANCE_TYPE_FARTHEST_MASK 2
#define DISTANCE_TYPE_AVERAGE_MASK  4
#define DISTANCE_TYPE_MAX           (DISTANCE_TYPE_NEAREST_MASK | DISTANCE_TYPE_FARTHEST_MASK | DISTANCE_TYPE_AVERAGE_MASK)
#define MAX_SUPPORTED_WORK_DISTANCE 400000000000000.00f  //< Float can go higher, but the uniform output can't
                                    
#define MAX_INPUT_BUFFER_SIZE 100
void main()
{
	char* input_str = (char*)malloc(MAX_INPUT_BUFFER_SIZE);
	
	float work_distance_ft;
	unsigned char distance_type;  // 0/N/n Nearest, 1/F/f Farthest, 2/A/a Average
	unsigned char number_of_planets_to_model;
	
	float distance_percentage;
	float distance_proportion_ft;
	unsigned long distance_ft;            // 4294967295
	unsigned char distance_inch;  // 0 to 12
		
	unsigned char n;	
	unsigned char working_distance_mask;
	unsigned char max_planet_distance_data_index;
	unsigned char job_to_do;	
	unsigned char temp_index;
	unsigned char i;
	
	size_t max_buffer_size = MAX_INPUT_BUFFER_SIZE;
	
	// DIAMETER OF EARTH = 41.804 million′ = 41804000
	// DIAMETER OF SOLAR SYSTEM = 287.46 billion km  (to Sedna)
	// DISTANCE FROM SUN TO PLUTO = 3.67 billion miles (average)	
	// DISTANCE FROM SUN TO NEPTUNE = 2.781 billion mi      == 14,683,680,000,000 feet
	// MIN/MAX OF FLOAT == 1.175494351 E-38	3.402823466 E + 38
	
	// 1 AU   =             4.908e+11 ft
	// 1 AU   =    490,806,662,372.05 ft  (http://convert-to.com/conversion/length/convert-au-to-ft.html)
	// 10 AU  =  4,908,066,623,720.5  ft
	// 100 AU = 49,080,666,237,205.0  ft   == 14,959,787,069.1 KM
	//          14,683,680,000,000    ft  (radius of Neptune)   14683680000000
	//         400,000,000,000,000.00 ft  MAX SUPPORTED  (27X the radius of Neptune, 400 div 14.6)		
	                       
	//work_distance_ft = 4000000000.00f;  // threshold of ft ich to AU	
	//work_distance_ft = 5000000.0f;  // threshold of ft ich to EARTH-DIAMETER
	//work_distance_ft = 10000.0f;  // threshold of ft ich to miles
	//work_distance_ft = 41804000.0f;  // Diameter of Earth in FT
	//work_distance_ft = 14683680000000;  // Sun to Neptune in FT (typical)
	
#ifdef SSC_TEST_MODE

	work_distance_ft = DEFAULT_WORK_DISTANCE_FT;  //< Should be DEFAULT_WORK_DISTANCE_FT ?
	distance_type = 7;
	number_of_planets_to_model = 8;
	
#else
	
	if (input_str == NULL)
	{
		printf("UNABLE TO ALLOCATE BUFFER\n");
		return;
	}
	
	input_str[0] = '\0';  //< Make the input_str BLANK by default
	while (TRUE)
	{
	  printf("work distance (ft) [%3.2f]: ", DEFAULT_WORK_DISTANCE_FT);
#ifdef USE_GETS
		gets(input_str);
#else
		getline(&input_str, &max_buffer_size, stdin);
#endif
		if (input_str[0] == 0x0A) input_str[0] = '\0';  // ENTER
		if (input_str[0] == 0x20) input_str[0] = '\0';  // SPACE
		n = strlen(input_str);
		if (n == 0)
		{
			printf("defaulted\n");
			work_distance_ft = DEFAULT_WORK_DISTANCE_FT;
		}
		else
		{
			sscanf(input_str, "%f", &work_distance_ft);
		}
		
		// Now do the range checking...
		if (
		  (work_distance_ft < 0.001)
			|| (work_distance_ft > MAX_SUPPORTED_WORK_DISTANCE)  //< While FLOAT can support larger, our table output can't.
		)
		{
			printf("invalid (%f)\n", work_distance_ft);
		}
		else
		{
			break;
		}
	}
	
	input_str[0] = '\0';  //< Make the input_str BLANK by default
	while (TRUE)
	{
		distance_type = DISTANCE_TYPE_NONE;
	  printf("distance type (1/n nearest, 2/f farthest, 4/a average) [%d]: ", DISTANCE_TYPE_MAX);
#ifdef USE_GETS
		gets(input_str);
#else
		getline(&input_str, &max_buffer_size, stdin);
#endif
		if (input_str[0] == 0x0A) input_str[0] = '\0';  // ENTER
		if (input_str[0] == 0x20) input_str[0] = '\0';  // SPACE
		n = strlen(input_str);
		if (n == 0)
		{
			printf("defaulted\n");
			distance_type = DISTANCE_TYPE_MAX;
		}
		else
		{
			sscanf(input_str, "%c", &distance_type);  // First see if they entered a character (N/F/A)
  		if (
				(distance_type == 'N')
				|| (distance_type == 'n')
			) 
			  distance_type = DISTANCE_TYPE_NEAREST_MASK;
			else if (
				(distance_type == 'F')
				|| (distance_type == 'f')
			) 
			  distance_type = DISTANCE_TYPE_FARTHEST_MASK;
			else if (
				(distance_type == 'A')
				|| (distance_type == 'a')
			) 
			  distance_type = DISTANCE_TYPE_AVERAGE_MASK;
			else 
				distance_type -= '0';  //< Interpret as an ASCII 0-9 input and shift it back into a numerical 0-9 input  (assumes 0-9 are sequential in the character set)
		}
		
		// Now do the range checking...
		if (
		  (distance_type == DISTANCE_TYPE_NONE)
		  || (distance_type > DISTANCE_TYPE_MAX)  // 0000 0111  (3 options)
		)
		{
			printf("invalid (%d) [max %d]\n", distance_type, DISTANCE_TYPE_MAX);
		}
		else
		{
			break;
		}
	}
	
	input_str[0] = '\0';  //< Make the input_str BLANK by default
	while (TRUE)
	{
		printf("number of planets to model [8]: ");
#ifdef USE_GETS
		gets(input_str);
#else
		getline(&input_str, &max_buffer_size, stdin);
#endif
		if (input_str[0] == 0x0A) input_str[0] = '\0';  // ENTER
		if (input_str[0] == 0x20) input_str[0] = '\0';  // SPACE
		n = strlen(input_str);
		if (n == 0)
		{
			printf("defaulted\n");
			number_of_planets_to_model = 8;
		}
		else	
		{
			sscanf(input_str, "%c", &number_of_planets_to_model);
			number_of_planets_to_model -= '0';  //< Interpret as an ASCII 0-9 input and shift it back into a numerical 0-9 input  (assumes 0-9 are sequential in the character set)
		}
		
		// Now do the range checking...
		if (
		  (number_of_planets_to_model < 1)
			|| (number_of_planets_to_model > NUM_PLANETS)
		)
		{
			printf("invalid (%d)\n", number_of_planets_to_model);			
		}
		else
		{
			break;
		}
	}	
#endif
	
	free(input_str);
	
	// ******************************************************************
	// OUTPUT
	// ******************************************************************
	
	printf("first %d planets scaled to %3.4f ft...\n", 
	  number_of_planets_to_model,
		work_distance_ft
	);
	
	max_planet_distance_data_index = (number_of_planets_to_model-1)*3;	
	
  printf("         ");
	working_distance_mask = DISTANCE_TYPE_NEAREST_MASK;	
	while (TRUE)
	{
		job_to_do = (distance_type & working_distance_mask);
		
		if (job_to_do > 0)
		{
			if (job_to_do == DISTANCE_TYPE_NEAREST_MASK) temp_index = INDEX_NEAREST;
			else if (job_to_do == DISTANCE_TYPE_FARTHEST_MASK) temp_index = INDEX_FARTHEST;
			else if (job_to_do == DISTANCE_TYPE_AVERAGE_MASK) temp_index = INDEX_AVERAGE;			
			
			switch (temp_index)
			{
				                       //  1234567890
			case INDEX_NEAREST:  printf("nearest   "); break;
			case INDEX_FARTHEST: printf("farthest  "); break;
			case INDEX_AVERAGE:  printf("average   "); break;
			default:             printf("error     "); break;
			}			
		}
		
		working_distance_mask <<= 1;
		if (working_distance_mask > DISTANCE_TYPE_MAX)
		{
			break;
		}										
	}
	printf("\n");
		
  for (i = 0; i < number_of_planets_to_model; ++i)
	{
		printf("%-8s", planet_names[i]);
		
		working_distance_mask = DISTANCE_TYPE_NEAREST_MASK;	
		while (TRUE)
		{
			job_to_do = (distance_type & working_distance_mask);
			
			if (job_to_do > 0)
			{
				if (job_to_do == DISTANCE_TYPE_NEAREST_MASK) temp_index = INDEX_NEAREST;
				else if (job_to_do == DISTANCE_TYPE_FARTHEST_MASK) temp_index = INDEX_FARTHEST;
				else if (job_to_do == DISTANCE_TYPE_AVERAGE_MASK) temp_index = INDEX_AVERAGE;			
				
				distance_percentage = 
					planet_distance_data[(i*3)+temp_index][INDEX_MIL_MI] 
						/
					planet_distance_data[max_planet_distance_data_index+INDEX_FARTHEST][INDEX_MIL_MI];
					
				distance_proportion_ft = distance_percentage * work_distance_ft;				
								
        // There are two reasons for the following output-unit adjustment:                
				// 1) to fit the result in 32-bit long
				// 2) to fit the result within the 
				if (work_distance_ft >= 4000000000.00f)
				{   // valid until 400000000000000.00f then need another larger unit
					// SWITCH TO AU   
					printf("%07.3fau ", distance_proportion_ft / 490806662401.57f);					
				}
				else if (work_distance_ft >= 5000000.0f) 
				{
					// SWITCH TO EARTH-DIAMETER
					printf("%07.3fed ", distance_proportion_ft / 41804000.0f);
				}
				else if (work_distance_ft >= 10000.0f)
				{
					// SWITCH TO MILES
				  printf("%07.3fmi ", distance_proportion_ft / 5280.0);
				}
				else if (work_distance_ft < 9.0f)
				{
					// SWITCH TO mm
				  printf("%07.3fmm ", distance_proportion_ft * 304.8);
				}				
				else  // range of 9 to 10000.0 we keep output units in FT
				{			
          // output default of FEET and INCHES			
				  distance_ft = distance_proportion_ft;
				  distance_inch = (distance_proportion_ft - (float)distance_ft) * 12;
				  printf("%03lu' %03d\" ", distance_ft, distance_inch);
				}
			}
			
    	working_distance_mask <<= 1;
			if (working_distance_mask > DISTANCE_TYPE_MAX)
			{
				break;
			}										
		}
		printf("\n");
		
#ifdef ABBREVIATED_MODE		
    // SKIP the data portions - while it's interesting for reference, those interested can look it up or review the code
#else
		printf(" mkm/mmi ");
		working_distance_mask = DISTANCE_TYPE_NEAREST_MASK;	
		while (TRUE)
		{
			job_to_do = (distance_type & working_distance_mask);
			
			if (job_to_do > 0)
			{
				if (job_to_do == DISTANCE_TYPE_NEAREST_MASK) temp_index = INDEX_NEAREST;
				else if (job_to_do == DISTANCE_TYPE_FARTHEST_MASK) temp_index = INDEX_FARTHEST;
				else if (job_to_do == DISTANCE_TYPE_AVERAGE_MASK) temp_index = INDEX_AVERAGE;
		
				job_to_do = (i*3)+temp_index;
				printf("%04.0f/%04.0f ", 
					planet_distance_data[job_to_do][INDEX_MIL_KM],
					planet_distance_data[job_to_do][INDEX_MIL_MI]
				);	
			}

    	working_distance_mask <<= 1;
			if (working_distance_mask > DISTANCE_TYPE_MAX)
			{
				break;
			}								
		}
		printf("\n");

    printf(" au      ");
		working_distance_mask = DISTANCE_TYPE_NEAREST_MASK;	
		while (TRUE)
		{
			job_to_do = (distance_type & working_distance_mask);
			
			if (job_to_do) 
			{
				if (job_to_do == DISTANCE_TYPE_NEAREST_MASK) temp_index = INDEX_NEAREST;
				else if (job_to_do == DISTANCE_TYPE_FARTHEST_MASK) temp_index = INDEX_FARTHEST;
				else if (job_to_do == DISTANCE_TYPE_AVERAGE_MASK) temp_index = INDEX_AVERAGE;
		
				job_to_do = (i*3)+temp_index;
				printf("%09.3f ", 
					planet_distance_data[job_to_do][INDEX_AU]				
				);		
			}
			
    	working_distance_mask <<= 1;
			if (working_distance_mask > DISTANCE_TYPE_MAX)
			{
				break;
			}						
		}
		printf("\n");
#endif
	}			
	
}

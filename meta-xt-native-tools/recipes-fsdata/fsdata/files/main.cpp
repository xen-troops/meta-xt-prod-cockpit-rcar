
#include <dirent.h>
#include <stdio.h>
#include <stdint.h> 
#include <stdlib.h>
#include <string.h>

typedef struct FileData{
    uint8_t * data;
    size_t size;
    int address;
    char name[512];
} FileData_t;

typedef struct FN {
  char name[512];
}FN_t;

const FN_t originList[]={
    {"cluster_hazard_normal"},
    {"cluster_hazard_selected"},
    {"cluster_turn_left"},
    {"cluster_turn_left_off"},
    {"cluster_turn_right"},
    {"cluster_turn_right_off"},
    {"cluster_HighLightOff"},
    {"cluster_HighLightOn"},
    {"cluster_LowLightOff"},
    {"cluster_LowLightOn"},
    {"cluster_FanOff"},
    {"cluster_FanOn"},
    {"cluster_OilOff"},
    {"cluster_OilOn"},
    {"cluster_BatteryOff"},
    {"cluster_BatteryOn"},
    {"cluster_AirbagOff"},
    {"cluster_AirbagOn"},
    {"cluster_BeltOff"},
    {"cluster_BeltOn"},
    {"cluster_BrakeOff"},
    {"cluster_BrakeOn"},
    {"cluster_WindshieldOff"},
    {"cluster_WindshieldOn"},
    {"cluster_WipingOff"},
    {"cluster_WipingOn"},
    {"cluster_FuelEmptyOff"},
    {"cluster_FuelEmptyOn"},
    {"cluster_CoolingLiquidOff"},
    {"cluster_CoolingLiquidOn"},
    {"cluster_gear_p_off"},
    {"cluster_gear_p_on"},
    {"cluster_gear_r_off"},
    {"cluster_gear_r_on"},
    {"cluster_gear_n_off"},
    {"cluster_gear_n_on"},
    {"cluster_gear_d_off"},
    {"cluster_gear_d_on"},
    {"cluster_gear_s_off"},
    {"cluster_gear_s_on"},
    {"cluster_needle"},
    //{"1920x720_Dashboard_BG"},
    //{"cluster_background"},
    //{"cluster_background_sport"},
    //{"cluster_background_sport_2"},
    //{"Cluster_Display_bg2"},
    //{"MicrosoftTeams-image_center"},
    {"0"},
    {"1"},
    {"2"},
    {"3"},
    {"4"},
    {"5"},
    {"6"},
    {"7"},
    {"8"},
    {"9"},
    {"TIME_AM"},
    {"TIME_PM"},
    {"TIME_："},
    /*{"TRIP_A"},
    {"TRIP_B"},
    {"TRIP_B_1"},
    {"TRIP_KM"},
    {"TRIP_KM_1"},
    {"TRIP_A"},
    {"icon_cluster"},*/
    {"t_0"},
    {"t_1"},
    {"t_2"},
    {"t_3"},
    {"t_4"},
    {"t_5"},
    {"t_6"},
    {"t_7"},
    {"t_8"},
    {"t_9"},
    /*{"r1"},
    {"r2"},*/
    /*{"Gauge_Bar_5"}*/
   /* {"Gauge_Bar_10"},
    {"Gauge_Bar_20"},
    {"Gauge_Bar_30"},
    {"Gauge_Bar_40"},*/
    //{"Gauge-Bar_10"},
    //{"Gauge-Bar_20"},
    //{"Gauge-Bar_25"},
    //{"Gauge-Bar_30"},
    //{"Gauge-Bar_35"},
    //{"Gauge-Bar_40"},
    /*{"Gauge-Bar_45"},
    {"Gauge-Bar_50"},
    {"Gauge-Bar_55"},
    {"Gauge-Bar_60"},
    {"Gauge-Bar_65"},
    {"Gauge-Bar_70"},
    {"Gauge-Bar_75"},
    {"Gauge-Bar_76"},
    {"Gauge-Bar_80"},
    {"Gauge-Bar_85"},
    {"Gauge-Bar_90"}, */
  //  {"Cluster-Display-Sport"},
    /*{"5-MPH"},
    {"10-MPH"},
    {"15-MPH"},
    {"20-MPH"},*/
    /*{"25-MPH"},
    {"30-MPH"},
    {"35-MPH"},*/
    /*{"40-MPH"},
    {"45-MPH"},
    {"95-MPH"},
    {"100-MPH"},
    {"105-MPH"},
    {"110-MPH"},
    {"115-MPH"},
    {"120-MPH"},*/
    {"200"},
    {"400"},
    {"600"},
    {"800"},
    {"1000"},
    {"1200"},
    {"1400"},
    {"1600"},
    {"1800"},
    {"2000"},
    {"2200"},
    {"2400"},
    {"2600"},
    {"2800"},
    {"4200"},
    {"4000"},
    {"3800"},
    {"3600"},
    {"3400"},
    {"3200"},
    {"3000"},
    {"4400"},
    {"4800"},
    {"5000"},
    {"5200"},
    {"5400"},
    {"5600"},
    {"5800"},
    {"6000"},
    {"6200"},
    {"6400"},
    {"6600"},
    {"6800"},
    {"4600"},
    {"7000"},
    {"rpm9"},
    {"rpm8"},
    {"rpm7"},
    {"rpm6"},
    {"rpm5"},
    {"rpm4"},
    {"rpm3"},
    {"rpm2"},
    {"rpm1"},
    {"rpm0"},
    //{"Bg-with-all-the-bottom-center-info"},
    //{"Display_Sport_US_bg_footer_UI"},
    //{"Cluster_Display_Sport_Mode_US_bg"},
    //{"Bg-with-all-the-bottom-center-info-2"},
    {"Bar-1"},
    {"Bar-2"},
    {"Bar-3"},
    {"Bar-4"},
    {"D1"},
    {"D1I"},
    {"D2"},
    {"D3"},
    {"D4"},
    {"D5"},
    {"D6"},
    {"Gear-change-reminder-point"},
    {"sl0"},
    {"sl1"},
    {"sl2"},
    {"sl3"},
    {"sl4"},
    {"sl5"},
    {"sl6"},
    {"sl7"},
    {"sl8"},
    {"sl9"},
    //{"Speed-limit_US_bg-circle"},
    //{"speed-limit-white"},
    {"D-Rectangle"},
    {"TRIP_MI"},
    {"TRIP_KM"},
    {"TRIP_A"},
    {"TRIP_B"},  
    {"Cluster_Display_-Sport_Mode_US_footer-2"},
    {"P_on"},
    {"R_on"},
    {"N_on"},
    {"D_on"},  
    {"D_on_black"},
  //  {"Bg-without-all-the-bottom-center-info"},
    {"end"},
};


static char* remove_extension(const char* name, char* buffer, size_t size){
  const char* p= name;
  char* res = buffer;
  char* dot = buffer;
  while(*p != '\0') {
    *res = *p;
    if(*res == '.'){
      dot = res;
    }
    ++p;
    ++res;
    
  }
  if(dot != buffer){
    *dot = '\0';
  }
  return buffer;
}

static size_t get_file_data(const char* fileName, FileData_t& fileData) {
  auto file = fopen(fileName, "r");

  if(!file){
    return 0;
  }
  
  fseek(file, 0L, SEEK_END);
  fileData.size = ftell(file) - 18;
  fseek(file, 18, SEEK_SET);
  
  fileData.data = (uint8_t*)malloc(fileData.size);

  auto result = fread (fileData.data, sizeof(*fileData.data), fileData.size, file);
  
  if(result != fileData.size){
    free(fileData.data);
    fileData.data = NULL;
    fileData.size = 0;
  }
  else {
    sprintf(fileData.name, "%s.bin", fileData.name);
  }
  
  fclose(file);
  return fileData.size;
}

size_t get_padding(const FileData_t& fileData){
  return 512 * (int)(1+fileData.size/512);
}

static FILE* img_data = NULL;

static void add_tail(const FileData_t & fileData, size_t padding){
  for(auto i = fileData.size ; i < padding;i++){
     fprintf(img_data, "0x%02X, ", 0);
     if (i % 20 == 19)
     {
       fputc('\n', img_data);    
     }
  }
}

static void add_to_image_data(const FileData_t& fileData){
  for (auto iIndex = 0; iIndex < fileData.size; iIndex++)
  {
    fprintf(img_data, "0x%02X, ", ((uint8_t *)fileData.data)[iIndex]);
    if (iIndex % 20 == 19)
    {
      fputc('\n', img_data);    
    }
  }
}

static FILE* fs_data = NULL;

static void add_to_fs_data(const FileData_t& fileData){
  fprintf(fs_data, "{\"%s\", %i, (char*)0x%02X},\n", fileData.name, fileData.size, fileData.address);
}

static void process_directory(char* directory){

  DIR *d;
  struct dirent *dir;
  char szBuffer [512];
  d = opendir(directory);//"/home/iusyk/projects/langs/c++/tests/arraytobin/resize");
  if (d)
  {
    int address = 4026531840;
    while ((dir = readdir(d)) != NULL)
    {
      sprintf(szBuffer, "%s/%s", directory, dir->d_name);

      FileData_t fileData = {
              .data = NULL, 
              .size = 0, 
              .address = address
             };
      remove_extension(dir->d_name, fileData.name, sizeof(fileData.name)/sizeof(*fileData.name));

      get_file_data(szBuffer, fileData);
      if(fileData.data){
        
        add_to_image_data(fileData);
        auto padding = get_padding(fileData);
        add_tail(fileData, padding);
        add_to_fs_data(fileData);
        
        address += padding;

        if(fileData.data){
          free(fileData.data);
        }
      }      
    }
    closedir(d);
  }
}


static void process_files(char* directory){
  DIR *d;
  struct dirent *dir;
  char szBuffer [512];
  int address = 4026531840;
  const FN_t *f = originList;
  while(*f->name != 'e') {
    FileData_t fileData = {
            .data = NULL,
            .size = 0, 
            .address = address
            };
    sprintf(fileData.name, "%s", f->name);
    //remove_extension(f->name, szBuffer, sizeof(szBuffer)/sizeof(*szBuffer));
    sprintf(szBuffer, "%s/%s.tga",directory, f->name);
    get_file_data(szBuffer, fileData);
    if(fileData.data){

      add_to_image_data(fileData);
      auto padding = get_padding(fileData);
      add_tail(fileData, padding);
      add_to_fs_data(fileData);
        
      address += padding;

      if(fileData.data){
          free(fileData.data);
      }
    }
    ++f;
  }
}

int main (int argc, char *argv[]) { 

/*    if(argc < 3){
      printf("2 arguments are required :");
      printf("1.directory to scan the files \n");
      printf("2. generate all files from the direcotry or use the default list of the required files. \n");
      return 1;
    }
*/
    printf("Start ..");
    img_data = fopen("./image_data.c","w");
    if(!img_data){
      return 1;
    }

    fs_data = fopen("./fs_data.c","w");
    if(!fs_data){
      fclose(img_data);
      return 1;
    }

    fprintf(fs_data, "#include \"typedef.h\"\n");
    fprintf(fs_data, "#include \"romfs_api.h\"\n");
    fprintf(fs_data, "const eeRomFs_Data_t RomFileSystemData[]={\n");

    fprintf(img_data, "#include \"typedef.h\"\n");
    fprintf(img_data, "const uint8_t ClusterImageData[] = {\n");

    //process_directory("/home/iusyk/projects/prod-aos-migration/cockpit/yocto/vlib/app/2d-wow-cluster-demo/src/image/tga_resize");
    process_files("/home/iusyk/projects/langs/c++/tests/arraytobin/resize");
     
    fprintf(fs_data, "{\"\",0,0}\n");
    fprintf(fs_data, "};\n");
    fprintf(img_data, "};");

    fclose(fs_data);
    fclose(img_data);
    return 0;
}

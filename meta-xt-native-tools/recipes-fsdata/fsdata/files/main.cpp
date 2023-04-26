
#include <string.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>

class FileData{
  public:
    explicit FileData(const std::string & name, size_t size, int addr):
    mSize(size),
    mAddress(addr),
    mName(name)
    {
      mPaddedSize = 512 * (int)(1+mSize/512);
      mData = std::make_unique<char[]>(mSize + mPaddedSize);
      memset(mData.get(), 0, mSize + mPaddedSize);
    }

    size_t size()const{return mSize;}
    size_t paddedSize()const{return mPaddedSize;}
    std::string name()const{return mName;}

    void exportTo(void (*functor)(FileData*))
    {
       functor(this);
    }

    int address()const {return mAddress;}
    char* data()const {return mData.get();}

    private:
    size_t mSize;
    int mAddress;
    std::string mName;
    std::unique_ptr<char[]> mData;
    size_t mPaddedSize;
};

int main (int argc, char *argv[]) {
  if(argc < 3){
    std::cout << "Error: number of parameters are less than 2, 1st - input folder , 2nd - output folder" << std::endl;
    return 1;
  }

  auto file_name = [](const std::string & name)->std::string {
    size_t lastindex = name.find_last_of("."); 
    return name.substr(0, lastindex); 
  };
  /* save images in the array to process in cr7*/
  auto save_image = [](std::ofstream & file, const FileData & fData) {
    auto size = /*fData.size() + */fData.paddedSize();
    auto buffer = fData.data();
    
    auto charToHex = [](const char& c)->std::string {
      std::stringstream ss;
      ss << std::setw(2) << std::setfill('0') << std::hex << int{c};
      return ss.str().substr(ss.str().size() -2, ss.str().size());
    };
    
    std::ios_base::fmtflags f(file.flags());
    
    for (auto i = 0; i < size; i++)
    {
      file << "0x"
           << charToHex(buffer[i])
           << ", "; 
      if (i % 20 == 19)
      {
        file << std::endl;
      }
    }
    
    file.flags(f);
  };
  /* prepare the source .c file to define the place of the image in the array*/
  auto save_src = [](std::ofstream & file, const FileData & fData) {
    file << "{\"" 
        << fData.name()
        << ".bin"
        << "\", " << fData.size()
        << ", (char*)0x";

    std::ios_base::fmtflags f(file.flags());
    
    file << std::hex
        << int(fData.address());
    
    file.flags(f);
    
    file << "},"
        << std::endl;
  };

  std::cout << "Input folder is: " << argv[1] << std::endl;
  std::cout << "Output folder is: " << argv[2] << std::endl;

  std::string input_path = argv[1];
  std::string output_path = argv[2];

  std::ofstream img_file(output_path+"/ImageData.c");
  std::ofstream src_file(output_path+"/fs_data.c");

  src_file << "#include \"typedef.h\"" << std::endl;
  src_file << "#include \"romfs_api.h\"" << std::endl;
  src_file << "const eeRomFs_Data_t RomFileSystemData[]={" << std::endl;

  img_file << "#include \"typedef.h\"" << std::endl;
  img_file << "const uint8_t ClusterImageData[] = {" << std::endl;

  int addr = 4026531840;

  for (const auto & entry : std::filesystem::directory_iterator(input_path)){

    std::cout << entry.path() << std::endl;
    
    if (std::filesystem::is_directory(entry.path()))
      continue;

    auto fName = file_name(entry.path().filename().string());
    std::ifstream inFile(entry.path(), std::ios::in| std::ios::binary|std::ios::ate);

    if (inFile.is_open())
    {
        auto size = inFile.tellg() - std::streampos(18);
        std::cout << "File: " << entry.path() << " , size: " << size << std::endl;

        FileData fileData(fName, size, addr);
        
        inFile.seekg (18, std::ios::beg);
        inFile.read (fileData.data(), fileData.size());   
        inFile.close();

        save_image(img_file, fileData);
        save_src(src_file, fileData);

        addr+= fileData.paddedSize();
    }
  }

  src_file << "{\"\",0,0}" << std::endl;
  src_file << "};" << std::endl;
  img_file << "};";


  img_file.close();
  src_file.close();
  return 0;
}

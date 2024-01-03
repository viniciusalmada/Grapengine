#ifndef GRAPHIC_ENGINE3D_GE_IO_HPP
#define GRAPHIC_ENGINE3D_GE_IO_HPP

class IO
{
public:
  static std::string ReadFileToString(const std::filesystem::path& path);
};

#endif // GRAPHIC_ENGINE3D_GE_IO_HPP

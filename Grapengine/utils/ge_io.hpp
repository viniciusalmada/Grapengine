#ifndef GRAPENGINE_IO_HPP
#define GRAPENGINE_IO_HPP

namespace GE
{
  class IO
  {
  public:
    static std::string ReadFileToString(const std::filesystem::path& path);
  };
}

#endif // GRAPENGINE_IO_HPP

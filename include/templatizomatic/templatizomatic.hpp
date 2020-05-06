
#ifndef TEMPLETIZZOMATIC_SITE_HEADER_HPP
#define TEMPLETIZZOMATIC_SITE_HEADER_HPP

#include "mustache.hpp"

#include <map>
#include <memory>
#include <string>
#include <utility>

// https://bootsnipp.com
namespace templatizomatic {

using Data = kainjow::mustache::data;
using Blender = kainjow::mustache::mustache;

class Tpl {
  std::string sTemplate{""};

 public:
  explicit Tpl(std::string tpl) : sTemplate{std::move(tpl)} {}

  Tpl() = delete;
  ~Tpl() = default;

  [[nodiscard]]
  const std::string& getTemplate() const;
};

class Templatizomatic {
  std::map<std::string, std::unique_ptr<Tpl>> tpls{};
  std::map<std::string, std::string> siteData{};

 private:
  
  void myreplace(std::string& str, const std::string& from,
                 const std::string& to);

 public:
  void init(void* params);
  void loadFile(const std::string& filePath, std::string& buffer);
  void addTemplate(const std::string& key, const std::string& content);
  void loadTemplates(const std::string& tPath);
  const Tpl* getTemplete(const std::string& name);

 public:
  void addSiteData(std::string_view name, std::string_view data);

 public:
  void fillSiteData(templatizomatic::Data& data);

  void dump();
};
}  // namespace templatizomatic

#endif  //

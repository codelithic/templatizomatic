
#ifndef MONKEYCRYPT_COM_BOOTSTRAPFORM_HPP
#define MONKEYCRYPT_COM_BOOTSTRAPFORM_HPP

#include <list>
#include <memory>
#include <ostream>
#include <string>

namespace templatizomatic::bootstrap {

class Object {
 public:
  std::string name, id, value;

  virtual ~Object(){
  }

 public:
  virtual void write(std::ostream& os) = 0;
};

class Widget : public Object {
 public:
  explicit Widget(std::string lbl):Object(),Label(std::move(lbl)){}
  std::string Label,cssClass;
  std::string validfeedback, invalidFeedback;
  std::string helpMessage;

  bool hasDanger{false};

  ~Widget() override {
  }

 public:
  void write(std::ostream& os) override = 0;
};

class Button : public Widget {
 private:
  void init(){
    cssClass="btn-primary";
  }
 public:
  explicit Button(const std::string& lbl) : Widget(lbl) {
    init();
  }

  void write(std::ostream& os) override {
    os << R"(<button type="submit" class="btn btn-primary">)" << Label
       << R"(</button>)";
  }
  ~Button() final {
  }

};


class Submit : public Widget {
 public:
  explicit Submit(const std::string& lbl) : Widget(lbl) {}

  void write(std::ostream& os) override {
    os << R"(<button type="submit" class="btn btn-primary">)" << Label
       << R"(</button>)";
  }
  ~Submit() final {
  }

};

class Form {
  std::string Name;
  std::list<std::unique_ptr<Widget> > widgets;

 public:
  std::string Method{"POST"}, Action{"#"}, Enctype;  // multipart/form-data
  std::string Legend{"Legend"};

  void add( Widget* widget){
    widgets.emplace_back(std::unique_ptr<Widget>(widget) );
  }



  Form() = delete;
  explicit Form(std::string name) : Name(std::move(name)) {}
  ~Form() = default;

  void write(std::ostream& os) {
    os << R"(<form method=")" << Method << R"(" action=")" << Action << R"(" )";
    if (!Enctype.empty()) {
      os << R"(enctype=")" << Enctype << R"(" )";
    }
    os << "><fieldset>";
    os << "<legend>" << Legend << "</legend>";

    for (auto& widget : widgets) {
      widget->write(os);
    }

    os << "</fieldset></form>";
  }
};

}  // namespace templatizomatic::bootstrap

//using namespace templatizomatic::bootstrap;
//Form form("TEST");
//form.Enctype="multipart/form-data";
//form.Legend="LA PASSWORD";
//form.add(new Submit("CIAOONE"));
//form.write(os);


#endif  // MONKEYCRYPT_COM_BOOTSTRAPFORM_HPP

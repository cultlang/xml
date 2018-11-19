
#include "xml/common.h"

#include "all.h"

#include "lisp/library/system/prelude.h"
#include "lisp/semantics/cult/calling.h"

using namespace craft;
using namespace craft::lisp;
using namespace craft::types;
using namespace cultlang::pugixml;


typedef instance<pugi::xml_document> xdoc;
typedef instance<pugi::xml_node> xnode;
typedef instance<pugi::xml_node_iterator> xnodeit;
typedef instance<pugi::xml_named_node_iterator> xnnodeit;
typedef instance<pugi::xml_attribute> xattr;
typedef instance<pugi::xml_attribute_iterator> xattrit;

#define lMM sem->builtin_implementMultiMethod
#define HtP "xml"


CRAFT_TYPE_DEFINE(pugi::xml_document)
{
	_.add<GraphPropertyName>("pugixml/xml_document");
	_.add<GraphPropertyCppName>("pugi::xml_document");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<pugi::xml_document> _this) {
		return fmt::format("pugi::xml_document: {}", _this->name());
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<pugi::xml_document> _this) {
		return fmt::format("(pugi::xml_document)");
	});
}

CRAFT_TYPE_DEFINE(pugi::xml_node)
{
	_.add<GraphPropertyName>("pugixml/xml_node");
	_.add<GraphPropertyCppName>("pugi::xml_node");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<pugi::xml_node> _this) {
		return fmt::format("pugi::xml_node: {}", _this->name());
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<pugi::xml_node> _this) {
		return fmt::format("(pugi::xml_node)");
	});
}

CRAFT_TYPE_DEFINE(pugi::xml_attribute)
{
	_.add<GraphPropertyName>("pugixml/xml_attribute");
	_.add<GraphPropertyCppName>("pugi::xml_attribute");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<pugi::xml_attribute> _this) {
		return fmt::format("pugi::xml_attribute: {}={}", _this->name(), _this->value());
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<pugi::xml_attribute> _this) {
		return fmt::format("(pugi::xml_attribute {} {})", _this->name(), _this->value());
	});
}


typedef instance<std::string> tstr;

void cultlang::pugixml::make_pugixml_bindings(craft::instance<craft::lisp::Module> ret)
{
    auto sem = instance<CultSemantics>::make(ret);
    ret->builtin_setSemantics(sem);

    lMM(HtP"/load", [](tstr s) {
        auto res = instance<pugi::xml_document>::make();
        pugi::xml_parse_result result = res->load_file(s->c_str());
        if(result.status)
            throw stdext::exception(result.description());

        return res;
    });

    lMM(HtP"/parse", [](tstr s) {
        auto res = instance<pugi::xml_document>::make();
        pugi::xml_parse_result result = res->load_string(s->c_str());
        if(result.status)
            throw stdext::exception(result.description());
        return res;
    });

    lMM(HtP"/attribute", [](xdoc d, tstr s) { return xattr::make(d->attribute(s->c_str())); });
	lMM(HtP"/attribute", [](xnode d, tstr s) { return xattr::make(d->attribute(s->c_str())); });
    lMM(HtP"/attributes", [](xdoc d) { 
        std::vector<instance<>> res;
        for(auto i : d->attributes())
            res.push_back(xattr::make(i));

        return instance<lisp::library::List>::make(res);
    });
	lMM(HtP"/attributes", [](xnode d) { 
        std::vector<instance<>> res;
        for(auto i : d->attributes())
            res.push_back(xattr::make(i));

        return instance<lisp::library::List>::make(res);
    });

    lMM(HtP"/child", [](xdoc d, tstr s) { return xnode::make(d->child(s->c_str())); });
    lMM(HtP"/child", [](xnode d, tstr s) { return xnode::make(d->child(s->c_str())); });


    lMM(HtP"/children", [](xnode d) { 
        std::vector<instance<>> res;
        for(auto i : d->children())
            res.push_back(xnode::make(i));

        return instance<lisp::library::List>::make(res);
    });

	lMM(HtP"/children", [](xdoc d) { 
        std::vector<instance<>> res;
        for(auto i : d->children())
            res.push_back(xnode::make(i));

        return instance<lisp::library::List>::make(res);
    });

    lMM(HtP"/children", [](xnode d, tstr s) { 
        std::vector<instance<>> res;
        for(auto i : d->children(s->c_str()))
            res.push_back(xnode::make(i));

        return instance<lisp::library::List>::make(res);
    });

	 lMM(HtP"/children", [](xdoc d, tstr s) { 
        std::vector<instance<>> res;
        for(auto i : d->children(s->c_str()))
            res.push_back(xnode::make(i));

        return instance<lisp::library::List>::make(res);
    });
    
    
    //lMM(HtP"/attribute", [](xnode s, tstr a) {return xattr::make(s->attribute(a->c_str()));}


}

BuiltinModuleDescription cultlang::pugixml::BuiltinPugixml("cult/xml", cultlang::pugixml::make_pugixml_bindings);


#include "types/dll_entry.inc"
    

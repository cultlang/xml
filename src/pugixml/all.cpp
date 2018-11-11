
#include "pugixml/common.h"

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
typedef instance<pugi::xml_attribute> xattr;
typedef instance<pugi::xml_attribute_iterator> xattrit;

#define lMM sem->builtin_implementMultiMethod
#define HtP "pugixml"


CRAFT_TYPE_DEFINE(pugi::xml_document)
{
	_.add<GraphPropertyName>("pugixml/xml_document");
	_.add<GraphPropertyCppName>("pugi::xml_document");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<pugi::xml_document> _this) {
		return fmt::format("pugi::xml_document");
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<pugi::xml_document> _this) {
		return fmt::format("(pugi::xml_document)");
	});
}

typedef instance<std::string> tstr;

void cultlang::pugixml::make_pugixml_bindings(craft::instance<craft::lisp::Module> ret)
{
    auto sem = instance<CultSemantics>::make(ret);
    ret->builtin_setSemantics(sem);

    lMM(HtP"/loadFile", [](tstr s) {
        auto res = instance<pugi::xml_document>::make();
        pugi::xml_parse_result result = res->load_file(s->c_str());
        if(result.status)
            throw stdext::exception(result.description());

        return res;
    });

    lMM(HtP"/loadString", [](tstr s) {
        auto res = instance<pugi::xml_document>::make();
        pugi::xml_parse_result result = res->load_string(s->c_str());
        if(result.status)
            throw stdext::exception(result.description());
        return res;
    });

    lMM(HtP"/child", [](xdoc d, tstr s) { return xnode::make(d->child(s->c_str())); });
    lMM(HtP"/children", [](xdoc d, tstr s) { return xnodeit::make(d->children(s->c_str())); });

    lMM(HtP"/next", [](xnode n, xnodeit d) {
        if(*d == n->end()) return xnode(); 
        
        auto res = xnode::make(d->operator*());
        d->operator++();
        return res;
    });

    lMM(HtP"/next", [](xnode n, xnodeit d) {
        if(*d == n->end()) return xnode(); 
        
        auto res = xnode::make(d->operator*());
        d->operator++();
        return res;
    });

    //lMM(HtP"/attribute", [](xnode s, tstr a) {return xattr::make(s->attribute(a->c_str()));}


}

BuiltinModuleDescription cultlang::pugixml::BuiltinPugixml("cult/pugixml", cultlang::pugixml::make_pugixml_bindings);


#include "types/dll_entry.inc"
    

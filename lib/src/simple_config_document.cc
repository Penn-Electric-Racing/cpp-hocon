#include <hocon/config_parse_options.hpp>
#include <internal/simple_config_document.hpp>
#include <hocon/config_exception.hpp>
#include <internal/tokenizer.hpp>
#include <internal/config_document_parser.hpp>
#include <sstream>

using namespace std;

static std::string & trim_left(std::string & str) {
  auto it2 =  std::find_if( str.begin() , str.end() , 
          [](char ch){ return !std::isspace(ch); } );
  str.erase( str.begin() , it2);
  return str;   
}

static std::string & trim_right(std::string & str) {
  auto it1 =  std::find_if( str.rbegin() , str.rend() , 
          [](char ch){ return !std::isspace(ch); } );
  str.erase( it1.base() , str.end() );
  return str;   
}

static std::string & trim(std::string & str) {
   return trim_left(trim_right(str));
}


namespace hocon {
    simple_config_document::simple_config_document(shared_ptr<const config_node_root> root,
                                                   config_parse_options opts)
        : _config_node_tree(move(root)), _parse_options(move(opts)) {}

    unique_ptr<config_document> simple_config_document::with_value_text(string path, string new_value) const
    {
        if (new_value.empty()) {
            throw new config_exception("empty value for " + path + " passed to with_value_text");
        }

        shared_origin origin = make_shared<simple_config_origin>("single value parsing");
        token_iterator tokens {origin, unique_ptr<istream>{new stringstream(new_value)}, _parse_options.get_syntax()};
        shared_node_value parsed_value = config_document_parser::parse_value(move(tokens), origin, _parse_options);

        return unique_ptr<config_document>{new simple_config_document(
                _config_node_tree->set_value(path, parsed_value, _parse_options.get_syntax()),
                _parse_options)};
    }

    unique_ptr<config_document> simple_config_document::with_value(string path,
                                                                   shared_ptr<config_value> new_value) const
    {
        if (!new_value) {
            throw config_exception("null value for " + path + " passed to with_value");
        }
        config_render_options options = config_render_options();
        options = options.set_origin_comments(false);
        string rendered = new_value->render(options);
        trim(rendered);
        return with_value_text(path, rendered);
    }

    unique_ptr<config_document> simple_config_document::without_path(string path) const
    {
        return unique_ptr<config_document>{new simple_config_document(
                _config_node_tree->set_value(path, nullptr, _parse_options.get_syntax()), _parse_options)};
    }

    bool simple_config_document::has_path(string const& path) const
    {
        return _config_node_tree->has_value(path);
    }

    string simple_config_document::render() const
    {
        return _config_node_tree->render();
    }

    bool operator==(config_document const& lhs, config_document const& rhs)
    {
        return lhs.render() == rhs.render();
    }

}  // namespace hocon

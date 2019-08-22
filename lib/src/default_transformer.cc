#include <internal/default_transformer.hpp>
#include <hocon/config_value.hpp>
#include <internal/values/config_long.hpp>
#include <internal/values/config_double.hpp>
#include <internal/values/config_null.hpp>
#include <internal/values/config_boolean.hpp>
#include <internal/values/config_string.hpp>
#include <hocon/config_object.hpp>
#include <hocon/config_exception.hpp>

#include <sstream>

using namespace std;

namespace hocon {

    shared_value default_transformer::transform(shared_value value, config_value::type requested) {
        if (value->value_type() == config_value::type::STRING) {
            string s = value->transform_to_string();
            std::stringstream number_converter;
            switch (requested) {
                case config_value::type::NUMBER:
                    number_converter << s;
                    int64_t i;
                    number_converter >> i;
                    if (!number_converter.fail()) {
                        return make_shared<config_long>(value->origin(), i, s);
                    }
                    number_converter.str(std::string());

                    number_converter << s;
                    double d;
                    number_converter >> d;
                    if (!number_converter.fail()) {
                        return make_shared<config_double>(value->origin(), d, s);
                    }
                    break;
                case config_value::type::CONFIG_NULL:
                    if (s == "null") {
                        return make_shared<config_null>(value->origin());
                    }
                    break;
                case config_value::type::BOOLEAN:
                    if (s == "true" || s == "yes" || s == "on") {
                        return make_shared<config_boolean>(value->origin(), true);
                    } else if (s == "false" || s == "no" || s == "off") {
                        return make_shared<config_boolean>(value->origin(), false);
                    }
                    break;
                case config_value::type::LIST:
                    // can't go STRING to LIST automatically
                    break;
                case config_value::type::OBJECT:
                    // can't go STRING ot OBJECT automatically
                    break;
                case config_value::type::STRING:
                    // no-op, already a string
                    break;
                case config_value::type::UNSPECIFIED:
                    throw config_exception("No target value type specified");
            }
        } else if (requested == config_value::type::STRING) {
            // if we converted null to string here, then you wouldn't properly get a missing value error
            // i you tried to ge a null value as a string
            switch (value->value_type()) {
                case config_value::type::NUMBER:
                case config_value::type::BOOLEAN:
                    return make_shared<config_string>(value->origin(), value->transform_to_string(),
                                                      config_string_type::QUOTED);
                case config_value::type::CONFIG_NULL:
                    // this method will throw instead of returning null as a string
                    break;
                case config_value::type::OBJECT:
                    // can't convert OBJECT to STRING automatically
                    break;
                case config_value::type::LIST:
                    // can't convert LIST to STRING automatically
                    break;
                case config_value::type::STRING:
                    // no-op, already a string
                    break;
                case config_value::type::UNSPECIFIED:
                    throw config_exception("No target value type specified");
            }
        } else if (requested == config_value::type::LIST && value->value_type() == config_value::type::OBJECT) {
            // TODO: implement this later when we support complex config objects
            throw config_exception("We currently do not support lists");
        }

        return value;
    }


}  // namespace hocon

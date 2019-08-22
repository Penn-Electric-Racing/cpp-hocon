#include <hocon/config_value_factory.hpp>
#include <internal/values/config_null.hpp>
#include <internal/values/config_string.hpp>
#include <internal/values/config_long.hpp>
#include <internal/values/config_double.hpp>
#include <internal/values/config_int.hpp>
#include <internal/values/config_boolean.hpp>
#include <internal/values/simple_config_list.hpp>
#include <internal/values/simple_config_object.hpp>

namespace hocon {
    shared_value config_value_factory::from_any_ref(unwrapped_value value, std::string origin) {
        throw std::runtime_error("config_value_factory not implemented in non-boost version");
        return std::make_shared<config_null>(nullptr);
    }
}  // namespace hocon

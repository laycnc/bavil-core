

set(BVIL_CORE_PUBLIC_SOURCE_LISTS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/core/bavil_system.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/core/bavil_system_manager.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/core/bavil_multicast_delegate.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/core/bavil_object_base.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/core/bavil_object_handle.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/core/bavil_object_system.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/core/bavil_actor.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/core/bavil_world_system.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_angle.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_color4.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_colori4.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_euler.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_gram.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_math.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_math_def.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_math_function.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_matrix33.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_matrix43.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_matrix44.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_meter.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_quaternion.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_rect.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_vector2.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_vector3.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_vector4.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/public/math/bavil_rotator.h"
)

set(BVIL_CORE_PRIVATE_SOURCE_LISTS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/core/bavil_system_manager.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/core/bavil_object_handle.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/core/bavil_object_system.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/core/bavil_actor.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/core/bavil_world_system.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/math/bavil_color4.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/math/bavil_colori4.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/math/bavil_matrix33.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/math/bavil_matrix44.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/math/bavil_quaternion.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/math/bavil_vector2.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/math/bavil_vector3.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/math/bavil_vector4.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/private/math/bavil_rotator.cpp"
)


set(BVIL_CORE_NATVIS_LISTS
	"/src/natvis/bavil_object.natvis"
)

#ifndef _ALIAS_ECS_H_
#define _ALIAS_ECS_H_

#include <alias/utils.h>

/// @defgroup ecs Alias-ECS
/// @{
/** success and error codes returned by all functions that can fail
 */
typedef enum alias_ecs_Result {
  ALIAS_ECS_SUCCESS = 0,                       ///< command successfully completed
  ALIAS_ECS_ERROR_INVALID_ARGUMENT = -1,       ///< an argument given to the command is invalid
  ALIAS_ECS_ERROR_OUT_OF_MEMORY = -2,          ///< a memory allocation has failed
  ALIAS_ECS_ERROR_DOES_NOT_EXIST = -3,         ///< a requested object does not exist
  ALIAS_ECS_ERROR_INVALID_ENTITY = -4,         ///< something inside is broken, should not happen
  ALIAS_ECS_ERROR_INVALID_LAYER = -5,          ///< something inside is broken, should not happen
  ALIAS_ECS_ERROR_COMPONENT_EXISTS = -6,
  ALIAS_ECS_ERROR_COMPONENT_DOES_NOT_EXIST = -7,
} alias_ecs_Result;
/// @}

/// @defgroup instance Alias-ECS Instance
/// @{
/** opaque struct for Alias ECS Instance
 */
typedef struct alias_ecs_Instance alias_ecs_Instance;

/** Create an Alias-ECS instance.
 * 
 * @param[in] memory_callbacks
 *            may be NULL
 * 
 * @param[out] instance_ptr
 *             writes the newly allocated instance
 * 
 * @return
 *  - aeSUCCESS the instance was created and initialized successfully
 *  - aeERROR_INVALID_ARGUMENT memory_callbacks is not NULL but a function pointer within it was NULL
 *  - aeERROR_INVALID_ARGUMENT instance_ptr is NULL
 *  - aeERROR_OUT_OF_MEMORY a memory allocation failed
 */
alias_ecs_Result alias_ecs_create_instance(
    const alias_MemoryAllocationCallback * memory_callback
  , alias_ecs_Instance *                 * instance_ptr
);

/** Destructor for an Instance
 * 
 * frees all memory allocated by this instance and it-self.
 * 
 * @param[in] instance
 *            The instance to destory
 */
void alias_ecs_destroy_instance(alias_ecs_Instance * instance);
/// @}

/// @defgroup layer Alias-ECS Layer
/// @{
/** layers are represented by a single 64-bit integer */
typedef uint64_t alias_ecs_LayerHandle;

/** a value indicating an invalid layer value */
#define ALIAS_ECS_INVALID_LAYER 0xFFFFFFFF

/** data for creating a layer */
typedef struct alias_ecs_LayerCreateInfo {
  /** if this is non-zero, indicate the number of entities and max entities to allocate memory for */
  uint32_t max_entities;
} alias_ecs_LayerCreateInfo;

/** Create a Alias-ECS Layer
 *
 * @param[in] instance
 *            instance to create the layer for
 *
 * @param[in] create_info
 * 
 * @param[out] layer_ptr
 *             writes a value to be used to reference the created layer
 * 
 * @return
 *  - aeSUCCESS the layer was created
 *  - aeERROR_OUT_OF_MEMORY unable to allocate memory for this layer
 */
alias_ecs_Result alias_ecs_create_layer(
    alias_ecs_Instance              * instance
  , const alias_ecs_LayerCreateInfo * create_info
  , alias_ecs_LayerHandle           * layer_handle_ptr
);

/** flags used to describe behaviour for destorying a layer */
typedef enum alias_ecs_LayerDestroyFlags {
  ALIAS_ECS_LAYER_DESTROY_REMOVE_ENTITIES = 0x1,
} alias_ecs_LayerDestroyFlags;

/** Destructor for a Layer
 * 
 * @param[in] instance
 *            instance that the layer was created on
 * 
 * @param[in] unlink_entities
 *            if zero destroy the entities in this layer as well
 *            if non-zero, unlink the entities from the layer before destroying it
 * 
 * @param[in] layer
 *            the layer to destroy
 */
alias_ecs_Result alias_ecs_destroy_layer(
    alias_ecs_Instance          * instance
  , const alias_ecs_LayerHandle   layer_handle
  , alias_ecs_LayerDestroyFlags   flags
);

/** components are represented by a single 32-bit integer */

typedef uint32_t alias_ecs_ComponentHandle;

/** flags used to describe behaviour of a component when creating it */
typedef enum alias_ecs_ComponentCreateFlags {
  ALIAS_ECS_COMPONENT_CREATE_NOT_NULL = 0x1,
} alias_ecs_ComponentCreateFlags;

/** creation data for a component */
typedef struct alias_ecs_ComponentCreateInfo {
  /** flags */
 alias_ecs_ComponentCreateFlags flags;
 
  /** size of the data structure for this component */
  size_t size;

  /** number of required components */
  uint32_t num_required_components;

  /** pointer to memory of `num_required_components` aeComponents */
  const alias_ecs_ComponentHandle * required_components;
} alias_ecs_ComponentCreateInfo;
  
/** register a component with the instance
 *
 * @param[in] instance
 *            the instance to create register the component on
 * 
 * @param[in] create_info
 *            pointer to aeComponentCreateInfo; primary source of arguments for the function
 * 
 * @param[out] component_ptr
 *             writes a value to be used to reference the created component
 * 
 * @return
 *  - aeSUCCESS
 *  - aeERROR_INVALID_ARGUMENT 
 */
alias_ecs_Result alias_ecs_register_component(
    alias_ecs_Instance                  * instance
  , const alias_ecs_ComponentCreateInfo * create_info
  , alias_ecs_ComponentHandle           * component_ptr
);

/** entities are represented by a single 64-bit integer */
typedef uint64_t alias_ecs_EntityHandle;

/** this structure is used exclusivly by aeEntitySpawnInfo */
typedef struct alias_ecs_EntitySpawnComponent {
  /** the component this data represents */
  alias_ecs_ComponentHandle component;

  /** the stride of the memory pointed to by data
   * 
   * if non-zero, the stride that the data will be copied into the component data of the new entities.
   * if zero the stride is the same as the size of the component
   */
  uint32_t stride;

  /** pointer to the data to be copied into the spawned entities.
   * 
   * must be component size x aeEntitySpawnInfo::count in size at minimum
   */
  const void * data;
} alias_ecs_EntitySpawnComponent;

/** used for aeSpawn */
typedef struct alias_ecs_EntitySpawnInfo {
  /** the layer the entities will spawn into. can be aeINVALID_LAYER */
  alias_ecs_LayerHandle layer;

  /** the number of entities to spawn */
  uint32_t count;

  /** the number of components per entity */
  uint32_t num_components;

  /** pointer to num_components component data */
  const alias_ecs_EntitySpawnComponent * components;
} alias_ecs_EntitySpawnInfo;

/** spawn entities
 * 
 * Spawn's entities using the data provided
 * 
 * @param[in] instance
 *            the instance to create the entities in
 * 
 * @param[in] spawn_info
 *            data describing the components, layer, and data of the entities spawned
 * 
 * @param[out] entities_ptr
 *             if success, writes the entities into this memory
 * 
 * @return
 *  - aeSUCCESS                all entities spawned
 *  - aeERROR_DOES_NOT_EXIST   a component or layer specified does not exist
 *  - aeERROR_OUT_OF_MEMORY    ...
 *  - aeERROR_INVALID_ARGUMENT instance is NULL
 */
alias_ecs_Result alias_ecs_spawn(
    alias_ecs_Instance              * instance
  , const alias_ecs_EntitySpawnInfo * spawn_info
  , alias_ecs_EntityHandle          * entities_ptr
);

/** add data to an entity's component
 */
alias_ecs_Result alias_ecs_add_component_to_entity(
    alias_ecs_Instance        * instance
  , alias_ecs_EntityHandle      entity
  , alias_ecs_ComponentHandle   component
  , const void                * data
);

/** remove data from an entitiy */
alias_ecs_Result alias_ecs_remove_component_from_entity(
    alias_ecs_Instance        * instance
  , alias_ecs_EntityHandle      entity
  , alias_ecs_ComponentHandle   component
);

/** get a writable pointer to component data for an entity */
alias_ecs_Result alias_ecs_write_entity_component(
    alias_ecs_Instance        * instance
  , alias_ecs_EntityHandle      entity
  , alias_ecs_ComponentHandle   component
  , void *                    * out_ptr
);

/** get a read-only pointer to component data for an entity */
alias_ecs_Result alias_ecs_read_entity_component(
    alias_ecs_Instance        * instance
  , alias_ecs_EntityHandle      entity
  , alias_ecs_ComponentHandle   component
  , const void *              * out_ptr
);

/** kill an entity, removes it globally */
alias_ecs_Result alias_ecs_despawn(
    alias_ecs_Instance           * instance
  , uint32_t                       num_entities
  , const alias_ecs_EntityHandle * entities
);

typedef struct alias_ecs_Query alias_ecs_Query;

typedef void (* alias_ecs_QueryFN)(void * ud, alias_ecs_Instance * instance, alias_ecs_EntityHandle entity, void ** data);
typedef alias_Closure(alias_ecs_QueryFN) alias_ecs_QueryCB;

typedef enum alias_ecs_Filter {
  ALIAS_ECS_FILTER_EXCLUDE,
  ALIAS_ECS_FILTER_OPTIONAL,
  ALIAS_ECS_FILTER_MODIFIED
} alias_ecs_Filter;

typedef struct alias_ecs_QueryFilterCreateInfo {
  alias_ecs_Filter filter;
  alias_ecs_ComponentHandle component;
} alias_ecs_QueryFilterCreateInfo;

typedef struct alias_ecs_QueryCreateInfo {
  uint32_t num_write_components;
  const alias_ecs_ComponentHandle * write_components;

  uint32_t num_read_components;
  const alias_ecs_ComponentHandle * read_components;

  uint32_t num_filters;
  alias_ecs_QueryFilterCreateInfo * filters;
} alias_ecs_QueryCreateInfo;

alias_ecs_Result alias_ecs_create_query(
    alias_ecs_Instance              * instance
  , const alias_ecs_QueryCreateInfo * create_info
  , alias_ecs_Query *               * query_ptr
);

alias_ecs_Result alias_ecs_execute_query(
    alias_ecs_Instance * instance
  , alias_ecs_Query    * query
  , alias_ecs_QueryCB    cb
);

void alias_ecs_destroy_query(
    alias_ecs_Instance * instance
  , alias_ecs_Query    * query
);
/// @}

#endif // _ALIAS_ECS_H_


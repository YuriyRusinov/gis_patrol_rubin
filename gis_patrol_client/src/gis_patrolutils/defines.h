#ifndef _DEFINES_H_INCLUDED
#define _DEFINES_H_INCLUDED

#define _MAX_INT32_ 2147483647 //максимально допустимое значение для int32

#define PRIVILEGE_ERROR -2 //возникает если недостаточно дискреционных прав доступа
#define PRIVILEGE_ERROR1 -3 //возникает если была попытка изменить характеристики ИО, владельцем которого является не текущий КСА
#define ERROR_CODE -1
#define OK_CODE 1
#define IGNORE_CODE -2

//задает префикс для представлений основных системных таблиц. 
//Доступ к таким таблицам напрямую запрещен, только через view
#define VIEW_PREFIX ""

//задает нижнюю границу идентификаторов, с которых начинаются пользовательские справочники
//отличие пользовательских справочников от системных заключается в том, 
//что последние НЕ наследуют базовую таблицу q_base_table и НЕ имеют полей uuid_t и id_state
#define _MAX_SYS_IO_ID_ 300

//задает идентификатор системной категории, которая описывает таблицу с информационными объектами (io_objects)
//данный дефайн используется при представлении ИО в виде ЕИО
const int IO_CATEGORY_ID = 14;
const int IO_TABLE_CATEGORY_ID = 13;

//
//задает идентификатор системной категории, которая описывает таблицу с категориями
//
const int CAT_CATEGORY_ID = 12;
const int CAT_TABLE_CATEGORY_ID = 11;
const int CAT_TABLE_TYPE_ID = 10;


//
//задает идентификатор системной категории, которая описывает таблицу с атрибутами в категории
//
#define ATTRS_CAT_CATEGORY_ID 186
#define ATTRS_CAT_TABLE_CATEGORY_ID 185

//
//задает идентификатор системной категории, которая описывает таблицу с атрибутами в атрибутах
//
#define ATTRS_ATTR_CATEGORY_ID 190
#define ATTRS_ATTR_TABLE_CATEGORY_ID 189

//
// задают идентификаторы типов системных категорий
//
const int CAT_SYS_REF_ID = 8;
const int CAT_SYS_REF_CAT_ID = 9;


//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник состояний информационных объектов
const int IO_STATE_ID = 1;

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник типов категорий информационных объектов
const int IO_CAT_TYPE_ID = 2;

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник типов информационных объектов
#define IO_TYPE_ID 9

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник рубрик
const int IO_RUBR_ID = 38;
const int REC_ROOT_RUBR_ID = 1;

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник типов синхронизации информационных объектов
#define IO_SYNCTYPE_ID 39

// данный дефайн задает идентификатор системного информацоннного объекта,
// который описывает справочник доступных типов атрибутов
#define IO_ATTR_TYPE_ID 4

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочники атрибутов и групп атрибутов соответственно
const int IO_ATTR_ID = 5;
const int IO_ATTRS_GROUPS_ID = 83;

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник категорий
const int IO_CAT_ID = 6;

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник информационных объектов (т.е. сам себя)
const int IO_IO_ID = 7;

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник шаблонов информационных объектов
#define IO_TEMPLATE_ID 8



//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник пользователей
const int IO_USERS_ID = 25;

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник должностей
//#define IO_POS_ID 11

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник организаций
const int IO_ORG_ID = 27;

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник подразделений
#define IO_UNITS_ID 28

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник должностей (новая ОШС)
#define IO_POS_ID 26


//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает табель срочных донесений
#define IO_TSD_ID 15

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает журнал входящих и исходящих команд и распоряжений
#define IO_CMDJ_ID 17

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает журнал входящих и исходящих сообщений
#define IO_MSGJ_ID 20

//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник поисковых запросов 
const int IO_SEARCH_ID = 36;
//данный дефайн задает идентификатор системного информационного объекта, 
//который описывает справочник типов поисковых запросов 
const int IO_SEARCH_TYPE_ID = 10;

const int IO_INDICATOR_ID = 87;

// данный id задает идентификатор системного ИО,
// который описывает справочник потоков информационных сообщений
const int IO_MESSAGE_STREAM_ID = 94;

// данный id задает идентификатор системного ИО,
// описывающего справочники сценариев и вариантов соответственно
const int IO_SCENARIO_ID = 105;
const int IO_VARIANT_ID = 106;

//
// данный дефайн задает данные разработчика, описывающие сущность в древовидной структуре
//
const int USER_ENTITY = 137;

const int IO_LIFE_CYCLE_ID = 95;

//данный дефайн описывает идентификатор роли "остальные" в БД
#define OTHERS_ROLE -10

//идентификатор пользователя-администратора системы
//ему разрешены все операции
//в том числе по изменению привилегий на ИО, авторами которых он не является
#define ADMIN_ROLE 1

const int ATTR_ID = 1;
const int ATTR_NAME = 2;
#define ATTR_MACLABEL 63
#define ATTR_INPUT_NUMBER 99
#define ATTR_OUTPUT_NUMBER 100
#define ATTR_MESSAGE_BODY 45
const int ATTR_AUTHOR = 13;
const int ATTR_CODE = 6;
#define ATTR_COLUMN_NAME 9
const int ATTR_DESCRIPTION = 3;
#define ATTR_EXEC_DATETIME 37
#define ATTR_EXEC_PERIOD 38
#define ATTR_ID_A_TYPE 5
#define ATTR_CHILD 11
#define ATTR_ID_DL_CONTROLLER 36
#define ATTR_ID_DL_EXECUTOR 35
#define ATTR_ID_DL_FROM 42
#define ATTR_ID_DL_RECEIVER 52
#define ATTR_ID_DL_SENDER 51
#define ATTR_ID_DL_TO 34
const int ATTR_ID_IO_CATEGORY = 12;
#define ATTR_ID_IO_OBJECT 48
#define ATTR_ID_IO_OBJECT_ATT 167
const int ATTR_ID_IO_STATE = 18;
#define ATTR_ID_IO_TYPE 43
const int ATTR_ID_IO_CAT_TYPE = 10;
#define ATTR_ID_JR_STATE 41
#define ATTR_ID_MACLABEL ATTR_MACLABEL
#define ATTR_ID_OWNER_ORG 117
const int ATTR_ID_PARENT = 27;
#define ATTR_ID_PARENT1 84
#define ATTR_ID_SUBSTITUTOR 85
#define ATTR_ID_SEARCH_TEMPLATE 110
#define ATTR_ID_STATE 65
#define ATTR_INFORMATION 14
#define ATTR_INSERT_TIME 16
#define ATTR_IO_OBJECTS_ORGANIZATION 97
#define ATTR_ID_ORGANIZATION 74
#define ATTR_IS_ARCHIVED 40
#define ATTR_IS_AUTOMATED 44
#define ATTR_IS_GLOBAL 111
#define ATTR_IS_MAIN 17
const int ATTR_IS_SYSTEM = 15;
#define ATTR_SENT_DATETIME 54
#define ATTR_ID_URGENCY_LEVEL 165
const int ATTR_TABLE_NAME = 8;
const int ATTR_FIO = 25;
const int ATTR_RECORD_FILL_COLOR = 206;
const int ATTR_RECORD_TEXT_COLOR = 207;
#define ATTR_MAIL_LISTS_POSITION 166
#define ATTR_ID_SYNC_TYPE 112
#define ATTR_RECEIVE_DATETIME 55
#define ATTR_ACCEPTED_DATETIME 188
#define ATTR_READ_DATETIME 56
#define ATTR_OSNOVANIE 39
#define ATTR_REF_TABLE_NAME 216
#define ATTR_SHB 104
#define ATTR_ID_UNIT 31
#define ATTR_SHORT_NAME 19
#define ATTR_ID_HISTOGRAM_PARAMS_STREAMS 360
#define ATTR_ID_HISTOGRAM_PARAMS_CHAINS 361
const int ATTR_R_ICON = 312;
const int ATTR_UUID_T = 348;
const int ATTR_ID_TABLE_CATEGORY = 402;
const int ATTR_RR_NAME = 378;
const int ATTR_ITEM_IS_LEAF = 403;



//названия для переходных таблиц некоторых системных справочников
//имеющих атрибут типа atCheckListEx
#define ORGANIZATION_WORK_MODE "organization_work_mode"
#define TABLE_NOTIFIES_IO_OBJECTS "table_notifies_io_objects"
#define LIFE_CYCLE_IO_STATES "life_cycle_io_states"
#define IO_PROCESSING_ORDER_CHAINS "io_processing_order_chains"
#define UNITS_WORK_MODE "units_work_mode"
#define POSITION_WORK_MODE "position_work_mode"
#define IO_OBJECTS_ORGANIZATION "io_objects_organization"
//#define IO_CATEGORIES_ORGANIZATION "io_categories_organization"
#define USER_CHAINS_ORGANIZATION "user_chains_organization"
#define REPORT_ORGANIZATION "report_organization"

#define GUARD_OBJ_DEVICES_TSO "guard_objects_devices"
#define ACCESS_CARDS_ACCESS_PLAN_TSO "access_cards_access_plan"

#define MAIL_LISTS_POSITION "mail_lists_position"
#define SHU_DLS_POSITION "shu_dls_position"

#define _MAX_FILE_BLOCK 1000000 //1MB - размер блока файла, который вычитывается при передаче файла между клиентом и сервером
#define _MAX_FILE_BLOCK2 50000000  //50 MB - размер файла максимально разрешенный при передаче одним пакетом по транспорту информационного обмена. При больших размерах бьем на части
#define _MAX_FILE_BLOCK3 5000000  //5MB - размер блока файла, который должен передаваться по транспорту информационного обмена, если осуществляется передача файлов частями


//
//Форматы взаимодействия внешних систем
//
#define ID_INTERACTION_FORMAT_XML 1 //Унифицированный XML-формат взаимодействия внешних систем
#define ID_INTERACTION_FORMAT_PARAM_VALUE 2 //простой формат взаимодействия внешних систем на основе принципа ПАРАМЕТР=ЗНАЧЕНИЕ
#define ID_INTERACTION_FORMAT_SHUSHUN 3 //XML-формат (ЦНИИ ЭИСУ) взаимодействия внешних систем
#define ID_INTERACTION_FORMAT_DDOC 4 //внутренний формат взаимодействия систем DynamicDocs

const double pi=3.14159265358969;

#endif

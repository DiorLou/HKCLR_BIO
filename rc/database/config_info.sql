DROP TABLE IF EXISTS general_info;
CREATE TABLE general_info(
    key varchar(32) NOT NULL,
    value varchar(256) NOT NULL,
    PRIMARY KEY (key)
);

DROP TABLE IF EXISTS tp_config_info;
CREATE TABLE tp_config_info(
    tp_config_name varchar(32) NOT NULL,
    key varchar(32) NOT NULL,
    value varchar(256) NOT NULL,
    PRIMARY KEY (tp_config_name, key)
);

insert into general_info(key, value) values('TPConfigName', 'IS');
insert into general_info(key, value) values('RobotType', 'I5');
insert into general_info(key, value) values('DisablePluginList', '');
insert into general_info(key, value) values('DisableAddonList', '');
insert into general_info(key, value) values('AutoStart', 'false');

insert into tp_config_info(tp_config_name, key, value) values(
'IS', 'Theme', 'yellow');
insert into tp_config_info(tp_config_name, key, value) values(
'IS', 'Language', 'en_US');
insert into tp_config_info(tp_config_name, key, value) values(
'IS', 'RealRobotSimulationEnabled', 'true');
insert into tp_config_info(tp_config_name, key, value) values(
'IS', 'Resolution', '1280 * 800');

insert into tp_config_info(tp_config_name, key, value) values(
'CS', 'Theme', 'blue');
insert into tp_config_info(tp_config_name, key, value) values(
'CS', 'Language', 'en_US');
insert into tp_config_info(tp_config_name, key, value) values(
'CS', 'RealRobotSimulationEnabled', 'true');
insert into tp_config_info(tp_config_name, key, value) values(
'CS', 'Resolution', '1280 * 800');

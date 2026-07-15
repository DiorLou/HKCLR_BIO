DROP TABLE IF EXISTS system_info;
CREATE TABLE  system_info(
    key varchar(32) NOT NULL,
    value varchar(256) NOT NULL,
    PRIMARY KEY (key)
);

insert into system_info(key, value) values('ToolName', 'flange_center');
insert into system_info(key, value) values('InitPosition',
'-0.400319,-0.121499,0.547598,0.000002,0.707108,-0.707105,-0.000002,-0.000003,-0.127267,-1.321122,0.376934,-1.570796,-0.000008');
insert into system_info(key, value) values('DefaultProject', 'None#None');
insert into system_info(key, value) values('LockScreenEnabled', 'false');
insert into system_info(key, value) values('LockScreenTime', '500');
insert into system_info(key, value) values('IsDrawTrack', 'true');
insert into system_info(key, value) values('TrackDuration', '5');
insert into system_info(key, value) values('EnablePromptForDisclaimer', 'true');
insert into system_info(key, value) values('IsDisplayLineNumbers', 'true');
insert into system_info(key, value) values('isDisplayModePasswd', 'true');
insert into system_info(key, value) values('AntiShake', '150');
insert into system_info(key, value) values('SimTeachType', 'Simulator');
insert into system_info(key, value) values('IsLanguageInFactoryState', 'true');
insert into system_info(key, value) values('isDisplayMove2ReadyPoint', 'true');

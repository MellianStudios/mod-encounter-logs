DROP TABLE IF EXISTS `encounter_logs`;
CREATE TABLE `encounter_logs`
(
    `map_id`      SMALLINT UNSIGNED NOT NULL,
    `instance_id` SMALLINT UNSIGNED NOT NULL,
    `timestamp`   BIGINT UNSIGNED   NOT NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

DROP TABLE IF EXISTS `encounter_log_combats`;
CREATE TABLE `encounter_log_combats`
(
    `map_id`       SMALLINT UNSIGNED NOT NULL,
    `instance_id`  SMALLINT UNSIGNED NOT NULL,
    `guid`         INT UNSIGNED      NOT NULL,
    `state`        TINYINT UNSIGNED  NOT NULL,
    `max_hp`       INT               NOT NULL,
    `hp`           INT               NOT NULL,
    `max_resource` INT               NOT NULL,
    `resource`     INT               NOT NULL,
    `gear`         LONGTEXT,
    `talents`      LONGTEXT,
    `auras`        LONGTEXT,
    `timestamp`    BIGINT UNSIGNED   NOT NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

DROP TABLE IF EXISTS `encounter_log_spells`;
CREATE TABLE `encounter_log_spells`
(
    `map_id`            SMALLINT UNSIGNED NOT NULL,
    `instance_id`       SMALLINT UNSIGNED NOT NULL,
    `spell_id`          INT UNSIGNED      NOT NULL,
    `caster_owner_guid` INT UNSIGNED,
    `caster_guid`       INT UNSIGNED      NOT NULL,
    `caster_type`       TINYINT UNSIGNED  NOT NULL,
    `target_owner_guid` INT UNSIGNED,
    `target_guid`       INT UNSIGNED,
    `target_type`       TINYINT UNSIGNED,
    `cost`              INT UNSIGNED,
    `value`             INT,
    `overkill`          INT,
    `result`            TINYINT UNSIGNED,
    `flag`              SMALLINT UNSIGNED,
    `timestamp`         BIGINT UNSIGNED   NOT NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

DROP TABLE IF EXISTS `encounter_log_area_spells`;
CREATE TABLE `encounter_log_area_spells`
(
    `spell_id`          INT UNSIGNED     NOT NULL,
    `caster_owner_guid` INT UNSIGNED,
    `caster_guid`       INT UNSIGNED     NOT NULL,
    `caster_type`       TINYINT UNSIGNED NOT NULL,
    `target_owner_guid` INT UNSIGNED,
    `target_guid`       INT UNSIGNED     NOT NULL,
    `target_type`       TINYINT UNSIGNED NOT NULL,
    `value`             INT,
    `overkill`          INT,
    `result`            TINYINT UNSIGNED NOT NULL,
    `timestamp`         BIGINT UNSIGNED  NOT NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

DROP TABLE IF EXISTS `encounter_log_movements`;
CREATE TABLE `encounter_log_movements`
(
    `map_id`      SMALLINT UNSIGNED NOT NULL,
    `instance_id` SMALLINT UNSIGNED NOT NULL,
    `owner_guid`  INT UNSIGNED,
    `guid`        INT UNSIGNED      NOT NULL,
    `type`        TINYINT UNSIGNED  NOT NULL,
    `x`           DOUBLE            NOT NULL,
    `y`           DOUBLE            NOT NULL,
    `z`           DOUBLE            NOT NULL,
    `o`           DOUBLE            NOT NULL,
    `timestamp`   BIGINT UNSIGNED   NOT NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

DROP TABLE IF EXISTS `encounter_log_deaths`;
CREATE TABLE `encounter_log_deaths`
(
    `map_id`            SMALLINT UNSIGNED NOT NULL,
    `instance_id`       SMALLINT UNSIGNED NOT NULL,
    `owner_guid`        INT UNSIGNED,
    `guid`              INT UNSIGNED      NOT NULL,
    `type`              TINYINT UNSIGNED  NOT NULL,
    `killer_owner_guid` INT UNSIGNED,
    `killer_guid`       INT UNSIGNED      NOT NULL,
    `killer_type`       TINYINT UNSIGNED  NOT NULL,
    `timestamp`         BIGINT UNSIGNED   NOT NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

DROP TABLE IF EXISTS `encounter_logs`;
CREATE TABLE `encounter_logs`
(
    `map_id`      SMALLINT UNSIGNED NOT NULL,
    `instance_id` SMALLINT UNSIGNED NOT NULL,
    `state`       BIGINT UNSIGNED   NOT NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

DROP TABLE IF EXISTS `encounter_log_combats`;
CREATE TABLE `encounter_log_combats`
(
    `map_id`      SMALLINT UNSIGNED NOT NULL,
    `instance_id` SMALLINT UNSIGNED NOT NULL,
    `guid`        INT UNSIGNED      NOT NULL,
    `unit_type`   TINYINT UNSIGNED  NOT NULL,
    `state`       TINYINT UNSIGNED  NOT NULL,
    `timestamp`   BIGINT UNSIGNED   NOT NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

DROP TABLE IF EXISTS `encounter_log_spells`;
CREATE TABLE `encounter_log_spells`
(
    `map_id`      SMALLINT UNSIGNED NOT NULL,
    `instance_id` SMALLINT UNSIGNED NOT NULL,
    `spell_id`    INT UNSIGNED      NOT NULL,
    `caster_guid` INT UNSIGNED      NOT NULL,
    `target_guid` INT UNSIGNED,
    `cost_type`   TINYINT UNSIGNED  NOT NULL,
    `cost`        INT UNSIGNED,
    `value`       INT UNSIGNED,
    `result`      TINYINT UNSIGNED,
    `timestamp`   BIGINT UNSIGNED   NOT NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

DROP TABLE IF EXISTS `encounter_log_area_spells`;
CREATE TABLE `encounter_log_area_spells`
(
    `spell_id`    INT UNSIGNED     NOT NULL,
    `caster_guid` INT UNSIGNED     NOT NULL,
    `target_guid` INT UNSIGNED     NOT NULL,
    `value`       INT UNSIGNED,
    `result`      TINYINT UNSIGNED NOT NULL,
    `timestamp`   BIGINT UNSIGNED  NOT NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

DROP TABLE IF EXISTS `encounter_log_attacks`;
CREATE TABLE `encounter_log_attacks`
(
    `map_id`        SMALLINT UNSIGNED NOT NULL,
    `instance_id`   SMALLINT UNSIGNED NOT NULL,
    `attacker_guid` INT UNSIGNED      NOT NULL,
    `target_guid`   INT UNSIGNED      NOT NULL,
    `value`         INT UNSIGNED,
    `result`        TINYINT UNSIGNED  NOT NULL,
    `timestamp`     BIGINT UNSIGNED   NOT NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

DROP TABLE IF EXISTS `encounter_log_movements`;
CREATE TABLE `encounter_log_movements`
(
    `map_id`      SMALLINT UNSIGNED NOT NULL,
    `instance_id` SMALLINT UNSIGNED NOT NULL,
    `guid`        INT UNSIGNED      NOT NULL,
    `x`           DOUBLE            NOT NULL,
    `y`           DOUBLE            NOT NULL,
    `z`           DOUBLE            NOT NULL,
    `o`           DOUBLE            NOT NULL,
    `timestamp`   BIGINT UNSIGNED   NOT NULL
) ENGINE = InnoDB
  DEFAULT CHARSET = utf8mb4;

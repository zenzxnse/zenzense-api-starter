CREATE KEYSPACE IF NOT EXISTS zenzense
WITH replication = {'class': 'SimpleStrategy', 'replication_factor': 1};

USE zenzense;

CREATE TABLE IF NOT EXISTS users_by_id (
  user_id uuid PRIMARY KEY,
  email text,
  username text,

  password_hash text,
  password_algo text,

  first_name text,
  last_name text,
  dob date,                 

  phone text,
  country text,
  timezone text,

  avatar_url text,
  bio text,

  role text,                -- "user", "admin"
  status text,              -- "active", "banned", "deleted"

  email_verified boolean,
  email_verified_at timestamp,

  created_at timestamp,
  updated_at timestamp,
  last_login_at timestamp
);

CREATE TABLE IF NOT EXISTS users_by_email (
  email text PRIMARY KEY,
  user_id uuid
);

-- sessions (token auth)
CREATE TABLE IF NOT EXISTS sessions_by_token (
  session_token text PRIMARY KEY,
  user_id uuid,
  created_at timestamp,
  expires_at timestamp,
  ip text,
  user_agent text
);

-- per-user sessions listing 
CREATE TABLE IF NOT EXISTS sessions_by_user (
  user_id uuid,
  created_at timestamp,
  session_token text,
  expires_at timestamp,
  ip text,
  user_agent text,
  PRIMARY KEY (user_id, created_at)
) WITH CLUSTERING ORDER BY (created_at DESC);

CREATE TABLE IF NOT EXISTS audit_events_by_user (
  user_id uuid,
  ts timestamp,
  event_type text,          -- "login_ok", "login_fail", "password_change", etc
  ip text,
  user_agent text,
  meta text,                -- JSON string 
  PRIMARY KEY (user_id, ts)
) WITH CLUSTERING ORDER BY (ts DESC);
package commands;

import core.Data;

public interface Command {
  String execute(String[] paramArrayOfString, Data paramData);
}

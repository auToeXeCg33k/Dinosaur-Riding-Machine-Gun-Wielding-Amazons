package commands;

import core.Data;
import core.Report;

public interface Command {
  Report execute(String[] paramArrayOfString, Data paramData);
}

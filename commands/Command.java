package commands;

import core.Data;
import units.Report;

public interface Command {
  Report execute(String[] paramArrayOfString, Data paramData);
}

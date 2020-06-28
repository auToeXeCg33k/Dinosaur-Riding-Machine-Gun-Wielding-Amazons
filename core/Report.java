package core;

public class Report {
  private String print;
  
  private boolean code;
  
  public Report(String print, boolean code) {
    this.print = print;
    this.code = code;
  }
  
  public String getPrint() {
    return this.print;
  }
  
  public boolean getCode() {
    return this.code;
  }
}

namespace DataBase {
    using System;
    using System.Data;
    using System.Data.SqlServerCe;
    using System.Diagnostics;
    using System.Windows;
    using Microsoft.Win32;

    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window {
        #region Private State
        private SqlCeConnection sqlCeConnection;
        private DataRowView rowBeingEdited = null;
        private int lastSelectedIndex = -1;
        #endregion

        public MainWindow() {
            InitializeComponent();
        }

        #region Database
        private void InitData() {
            sqlCeConnection = new SqlCeConnection(@"Data Source=|DataDirectory|\Database1.sdf");
        }

        private void ShowAllData() {
            lastSelectedIndex = dataGrid1.SelectedIndex;
            DataRowView drv = (DataRowView)dataGrid1.CurrentItem;
            try {
                sqlCeConnection.Open();
                var cmd = new SqlCeCommand("Select * from sample", sqlCeConnection);
                var da = new SqlCeDataAdapter(cmd);
                var dt = new DataTable();
                da.Fill(dt);
                dataGrid1.DataContext = dt.DefaultView;
                dataGrid1.SelectedIndex = lastSelectedIndex;
            } catch (Exception ex) {
                Debug.WriteLine(ex);
            } finally {
                sqlCeConnection.Close();
            }
        }

        private void AddNew(int length) {
            if (length < 1) {
                return;
            }
            int changed = 0;
            try {
                sqlCeConnection.Open();
                var cmdd = new SqlCeCommand("select max(id) from sample", sqlCeConnection);
                int maxID = (int)cmdd.ExecuteScalar();
                Debug.WriteLine(maxID);

                string sql = "insert into sample(id) values(@id)";
                var cmd = new SqlCeCommand(sql, sqlCeConnection);
                for (int i = 0; i < length; ++i) {
                    cmd.Parameters.AddWithValue("@id", ++maxID);
                    changed += cmd.ExecuteNonQuery();
                    cmd.Parameters.Clear();
                }
            } catch (Exception ex) {
                Debug.WriteLine(ex);
            } finally {
                sqlCeConnection.Close();
            }
            if (changed > 0) {
                ShowAllData();
            }
        }

        private void UpdateData(DataRowView drv) {
            int changed = 0;
            try {
                string id = drv.Row["ID"].ToString();
                string title = drv.Row["Title"].ToString();
                string pubdate = drv.Row["PubDate"].ToString();
                string price = drv.Row["Price"].ToString();
                Debug.WriteLine(String.Format("{0}, {1}, {2}, {3}", id, title, pubdate, price));

                sqlCeConnection.Open();
                var cmd = new SqlCeCommand("update sample set title=@title,pubdate=@pubdate,price=@price where id=@id", sqlCeConnection);
                cmd.Parameters.AddWithValue("@id", id);
                cmd.Parameters.AddWithValue("@title", title);
                cmd.Parameters.AddWithValue("@pubdate", pubdate);
                cmd.Parameters.AddWithValue("@price", price);
                changed = cmd.ExecuteNonQuery();
                Debug.WriteLine("changed: " + changed);
            } catch (Exception ex) {
                Debug.WriteLine(ex);
            } finally {
                sqlCeConnection.Close();
            }
            if (changed > 0) {
                ShowAllData();
            }
        }

        private void DeleteData() {
            int changed = 0;
            try {
                DataRowView drv = (DataRowView)dataGrid1.CurrentItem;
                string id = drv.Row["ID"].ToString();
                sqlCeConnection.Open();
                var cmd = new SqlCeCommand("delete from sample where id=@id", sqlCeConnection);
                cmd.Parameters.AddWithValue("@id", id);
                changed = cmd.ExecuteNonQuery();
                Debug.WriteLine("changed: " + changed);
            } catch (Exception ex) {
                Debug.WriteLine(ex);
            } finally {
                sqlCeConnection.Close();
            }
            if (changed > 0) {
                ShowAllData();
            }
        }
        #endregion

        #region Export
        private void SaveCSV() {
            var sfd = new SaveFileDialog();
            sfd.FileName = "data.csv";
            sfd.DefaultExt = "*.csv";
            if (sfd.ShowDialog() == true) {
                using (var file = new System.IO.StreamWriter(sfd.FileName)) {
                    try {
                        sqlCeConnection.Open();
                        var cmd = new SqlCeCommand("Select * from sample", sqlCeConnection);
                        var reader = cmd.ExecuteReader();
                        cmd.Dispose();

                        while (reader.Read()) {
                            file.WriteLine(
                                reader["ID"].ToString() + "," +
                                reader["Title"].ToString() + "," +
                                reader["PubDate"].ToString() + "," +
                                reader["Price"].ToString());
                        }

                        reader.Close();
                    } catch (Exception ex) {
                        Debug.WriteLine(ex);
                    } finally {
                        sqlCeConnection.Close();
                    }
                }
            }
        }

        private void SaveHTML() {
            var sfd = new SaveFileDialog();
            sfd.FileName = "data.html";
            sfd.DefaultExt = "*.html";
            if (sfd.ShowDialog() == true) {
                using (var file = new System.IO.StreamWriter(sfd.FileName)) {
                    try {
                        sqlCeConnection.Open();
                        var cmd = new SqlCeCommand("Select * from sample", sqlCeConnection);
                        var reader = cmd.ExecuteReader();
                        cmd.Dispose();

                        // TODO: HTML Escape
                        file.WriteLine("<!DOCTYPE html>");
                        file.WriteLine("<meta charset=\"UTF-8\">");
                        file.WriteLine("<title>" + sfd.FileName + "</title>");
                        file.WriteLine("<table>");
                        file.WriteLine("<thead>");
                        file.WriteLine("<tr><th>ID<th>Title<th>PubDate<th>Price");
                        file.WriteLine("<tbody>");
                        while (reader.Read()) {
                            file.WriteLine(
                                "<tr><td>" + reader["ID"].ToString() +
                                "<td>" + reader["Title"].ToString() +
                                "<td>" + reader["PubDate"].ToString() +
                                "<td>" + reader["Price"].ToString());
                        }
                        file.WriteLine("</table>");

                        reader.Close();
                    } catch (Exception ex) {
                        Debug.WriteLine(ex);
                    } finally {
                        sqlCeConnection.Close();
                    }
                }
            }
        }
        #endregion

        #region Event
        private void Window_Loaded(object sender, RoutedEventArgs e) {
            InitData();
            ShowAllData();
        }

        private void button_Add_Click(object sender, RoutedEventArgs e) {
            int length = 0;
            try {
                length = int.Parse(textBox1.Text);
            } catch (Exception ex) {
                Debug.WriteLine(ex);
            }
            if (length > 0) {
                AddNew(length);
            }
        }

        private void MenuItem_Delete_Click(object sender, RoutedEventArgs e) {
            DeleteData();
        }

        private void dataGrid1_RowEditEnding(object sender, System.Windows.Controls.DataGridRowEditEndingEventArgs e) {
            DataRowView rowView = e.Row.Item as DataRowView;
            rowBeingEdited = rowView;
            Debug.WriteLine("RowEditEnding");
        }

        private void dataGrid1_CurrentCellChanged(object sender, EventArgs e) {
            if (rowBeingEdited != null) {
                rowBeingEdited.EndEdit();
                UpdateData(rowBeingEdited);
                rowBeingEdited = null;
            }
            Debug.WriteLine("CurrentCellChanged");
        }

        private void MenuItem_CSV_Click(object sender, RoutedEventArgs e) {
            SaveCSV();
        }

        private void MenuItem_HTML_Click(object sender, RoutedEventArgs e) {
            SaveHTML();
        }

        private void MenuItem_Exit_Click(object sender, RoutedEventArgs e) {
            this.Close();
        }
        #endregion
    }
}
using CommunityToolkit.Mvvm.ComponentModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client.Services
{
    public partial class LogService : ObservableObject
    {
        [ObservableProperty]
        private string? _log;

        public void Record(string message)
        {
            Log = message;
        }
    }
}

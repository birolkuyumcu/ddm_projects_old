//* Copyright (c) 2008, Stephen Stagg <stestagg@gmail.com>
//* All rights reserved.
//*
//* Redistribution and use in source and binary forms, with or without
//* modification, are permitted provided that the following conditions are met:
//*     * Redistributions of source code must retain the above copyright
//*       notice, this list of conditions and the following disclaimer.
//*     * Redistributions in binary form must reproduce the above copyright
//*       notice, this list of conditions and the following disclaimer in the
//*       documentation and/or other materials provided with the distribution.
//*     * Neither the name of offsetdesign.co.uk nor the
//*       names of its contributors may be used to endorse or promote products
//*       derived from this software without specific prior written permission.
//*
//* THIS SOFTWARE IS PROVIDED BY Stephen Stagg ''AS IS'' AND ANY
//* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//* DISCLAIMED. IN NO EVENT SHALL Stephen Stagg BE LIABLE FOR ANY
//* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

using System;
using System.Runtime.InteropServices;

public static class Fann
{
    public enum netType
    {
        FANN_NETTYPE_LAYER = 0, /* Each layer only has connections to the next layer */
        FANN_NETTYPE_SHORTCUT = 1/* Each layer has connections to all following layers */
    };



    public enum activationFunc
    {
        FANN_LINEAR = 0,
        FANN_THRESHOLD = 1,
        FANN_THRESHOLD_SYMMETRIC = 2,
        FANN_SIGMOID = 3,
        FANN_SIGMOID_STEPWISE = 4,
        FANN_SIGMOID_SYMMETRIC = 5,
        FANN_SIGMOID_SYMMETRIC_STEPWISE = 6,
        FANN_GAUSSIAN = 7,
        FANN_GAUSSIAN_SYMMETRIC = 8,
        /* Stepwise linear approximation to gaussian.
         * Faster than gaussian but a bit less precise.
         * NOT implemented yet.
         */
        FANN_GAUSSIAN_STEPWISE = 9,
        FANN_ELLIOT = 10,
        FANN_ELLIOT_SYMMETRIC = 11,
        FANN_LINEAR_PIECE = 12,
        FANN_LINEAR_PIECE_SYMMETRIC = 13,
        FANN_SIN_SYMMETRIC = 14,
        FANN_COS_SYMMETRIC = 15,
        FANN_SIN = 16,
        FANN_COS = 17
    };

    public enum errorFunc
    {
        FANN_ERRORFUNC_LINEAR = 0,
        FANN_ERRORFUNC_TANH
    };

    public enum stopFunc
    {
        FANN_STOPFUNC_MSE = 0,
        FANN_STOPFUNC_BIT
    };

    public class annOwner : IDisposable
    {
        public IntPtr ann;
        public annOwner(IntPtr ann)
        {
            this.ann = ann;
        }
        public void Dispose()
        {
            Fann.destroy(ann);
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct connection
    {
        /* Unique number used to identify source neuron */
        public uint from_neuron;
        /* Unique number used to identify destination neuron */
        public uint to_neuron;
        /* The numerical value of the weight */
        public float weight;
    };


    [DllImport("libfann.dll", EntryPoint = "fann_create_standard")]
    public static extern
        IntPtr create_standard(uint num_layers, __arglist);

    [DllImport("libfann.dll", EntryPoint = "fann_create_standard_array")]
    public static extern
        IntPtr create_standard_array(uint num_layers, uint[] layers);

    [DllImport("libfann.dll", EntryPoint = "fann_create_sparse")]
    public static extern
        IntPtr create_sparse(float connection_rate, uint num_layers, __arglist);

    [DllImport("libfann.dll", EntryPoint = "fann_create_sparse_array")]
    public static extern
        IntPtr create_sparse_array(float connection_rate, uint num_layers, uint[] layers);

    [DllImport("libfann.dll", EntryPoint = "fann_create_shortcut")]
    public static extern
        IntPtr create_shortcut(uint num_layers, __arglist);

    [DllImport("libfann.dll", EntryPoint = "fann_create_shortcut_array")]
    public static extern
        IntPtr create_shortcut_array(uint num_layers, uint[] layers);

    [DllImport("libfann.dll", EntryPoint = "fann_destroy")]
    public static extern
        void destroy(IntPtr ann);

    [DllImport("libfann.dll", EntryPoint = "fann_run")]
    static extern
        IntPtr internal_run(IntPtr ann, float[] input);

    public static float[] run(IntPtr ann, float[] input)
    {
        int outsize = (int)get_num_output(ann);
        IntPtr b = internal_run(ann, input);
        float[] o = new float[outsize];
        Marshal.Copy(b, o, 0, outsize);
        return o;
    }

    [DllImport("libfann.dll", EntryPoint = "fann_randomize_weights")]
    public static extern
        void randomize_weights(IntPtr ann, float min_weight, float max_weight);

    [DllImport("libfann.dll", EntryPoint = "fann_init_weights")]
    public static extern
        void init_weights(IntPtr ann, IntPtr train_data);

    [DllImport("libfann.dll", EntryPoint = "fann_print_connections")]
    public static extern
        void print_connections(IntPtr ann);

    [DllImport("libfann.dll", EntryPoint = "fann_print_parameters")]
    public static extern
        void print_parameters(IntPtr ann);

    [DllImport("libfann.dll", EntryPoint = "fann_get_num_input")]
    public static extern
        uint get_num_input(IntPtr ann);

    [DllImport("libfann.dll", EntryPoint = "fann_get_num_output")]
    public static extern
        uint get_num_output(IntPtr ann);

    [DllImport("libfann.dll", EntryPoint = "fann_get_total_neurons")]
    public static extern
        uint get_total_neurons(IntPtr ann);

    [DllImport("libfann.dll", EntryPoint = "fann_get_total_connections")]
    public static extern
        uint get_total_connections(IntPtr ann);

    [DllImport("libfann.dll", EntryPoint = "fann_get_network_type")]
    public static extern
        netType get_network_type(IntPtr ann);

    [DllImport("libfann.dll", EntryPoint = "fann_get_connection_rate")]
    public static extern
        float get_connection_rate(IntPtr ann);

    [DllImport("libfann.dll", EntryPoint = "fann_get_num_layers")]
    public static extern
        uint get_num_layers(IntPtr ann);

    [DllImport("libfann.dll", EntryPoint = "fann_get_layer_array")]
    static extern
        void get_layer_array(IntPtr ann, IntPtr layers);

    [DllImport("libfann.dll", EntryPoint = "fann_get_bias_array")]
    static extern
        void get_bias_array(IntPtr ann, IntPtr basis);

 //   public static uint[] get_layers(IntPtr ann)
 //   {
    //    uint layers = get_num_layers(ann);
    //    IntPtr l = Marshal.AllocHGlobal((int)(sizeof(uint) * layers));
    //    get_layer_array(ann, l); uint[] l2 = new uint[layers];
    //    unsafe
    //    {
    //        uint* lp = (uint*)l.ToPointer();
    //        for (int i = 0; i < layers; ++i) { l2[i] = lp[i]; }
    //    }
    //    Marshal.FreeHGlobal(l);
    //    return l2;
    //}

    //public static uint[] get_biass(IntPtr ann)
    //{
    //    uint layers = get_num_layers(ann);
    //    IntPtr l = Marshal.AllocHGlobal((int)(sizeof(uint) * layers));
    //    get_bias_array(ann, l); uint[] l2 = new uint[layers];
    //    unsafe
    //    {
    //        uint* lp = (uint*)l.ToPointer();
    //        for (int i = 0; i < layers; ++i) { l2[i] = lp[i]; }
    //    }
    //    Marshal.FreeHGlobal(l);
    //    return l2;
    //}

    //public static connection[] get_connections(IntPtr ann)
    //{
    //    uint connections = get_total_connections(ann);
    //    connection[] l2 = new connection[connections];
    //    IntPtr l = Marshal.AllocHGlobal((int)(Marshal.SizeOf(l2[0]) * connections));
    //    get_connection_array(ann, l);
    //    unsafe
    //    {
    //        connection* lp = (connection*)l.ToPointer();

    //        for (int i = 0; i < connections; ++i) { l2[i] = lp[i]; }
    //    }
    //    Marshal.FreeHGlobal(l);
    //    return l2;
    //}



    [DllImport("libfann.dll", EntryPoint = "fann_get_connection_array")]
    static extern
        void get_connection_array(IntPtr ann, IntPtr connections);

    [DllImport("libfann.dll", EntryPoint = "fann_set_weight_array")]
    static extern
        void set_weights(IntPtr ann, connection[] connections, uint num_connections);

    [DllImport("libfann.dll", EntryPoint = "fann_set_weight")]
    static extern
        void set_weight(IntPtr ann, uint from_neuron, uint to_neuron, float weight);

    [DllImport("libfann.dll", EntryPoint = "fannfann_set_user_data_set_weight")]
    static extern
        void set_user_data(IntPtr ann, IntPtr user_data);

    [DllImport("libfann.dll", EntryPoint = "fann_get_user_data")]
    static extern
        IntPtr get_user_data(IntPtr ann);

    public class Training
    {

        public enum train_algo
        {
            FANN_TRAIN_INCREMENTAL = 0,
            FANN_TRAIN_BATCH,
            FANN_TRAIN_RPROP,
            FANN_TRAIN_QUICKPROP
        };

        [DllImport("libfann.dll", EntryPoint = "fann_train")]
        static extern public
            void train(IntPtr ann, float[] input, float[] desired_output);

        [DllImport("libfann.dll", EntryPoint = "fann_test")]
        static extern
            IntPtr internal_test(IntPtr ann, float[] input,
            float[] desired_output);

        public static float[] test(IntPtr ann, float[] input, float[] desired_output)
        {
            int outsize = (int)get_num_output(ann);
            IntPtr b = internal_test(ann, input, desired_output);
            float[] o = new float[outsize];
            Marshal.Copy(b, o, 0, outsize);
            return o;
        }

        [DllImport("libfann.dll", EntryPoint = "fann_get_MSE")]
        static extern public
            float get_MSE(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_get_bit_fail")]
        static extern public
            uint get_bit_fail(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_reset_MSE")]
        static extern public
            void reset_MSE(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_train_on_data")]
        static extern public
            void train_on_data(IntPtr ann, IntPtr data, uint max_epochs, uint epochs_between_reports, float desired_error);

        [DllImport("libfann.dll", EntryPoint = "fann_train_on_file")]
        static extern public
            void train_on_file(IntPtr ann, String filename, uint max_epochs, uint epochs_between_reports, float desired_error);

        [DllImport("libfann.dll", EntryPoint = "fann_train_epoch")]
        static extern public
            float train_epoch(IntPtr ann, IntPtr data);

        [DllImport("libfann.dll", EntryPoint = "fann_test_data")]
        static extern public
            float test_data(IntPtr ann, IntPtr data);

        [DllImport("libfann.dll", EntryPoint = "fann_read_train_from_file")]
        static extern public
            IntPtr read_from_file(String filename);

        public delegate int train_callback(uint num, uint num_input, uint num_output, IntPtr input, IntPtr output);
        public delegate int report_callback(IntPtr nn, IntPtr data, uint max_epochs, uint epochs_between_reports, float desired_error, uint epochs);

        [DllImport("libfann.dll", EntryPoint = "fann_create_train_from_callback")]
        static extern public
            IntPtr create_from_callback(uint num_data, uint num_input, uint num_output, train_callback callback);

        [DllImport("libfann.dll", EntryPoint = "fann_destroy_train")]
        static extern public
            void destroy(IntPtr train_data);

        [DllImport("libfann.dll", EntryPoint = "fann_shuffle_train_data")]
        static extern public
            void shuffle_train_data(IntPtr train_data);

        [DllImport("libfann.dll", EntryPoint = "fann_scale_train")]
        static extern public
            void scale_train(IntPtr ann, IntPtr data);

        [DllImport("libfann.dll", EntryPoint = "fann_descale_train")]
        static extern public
            void descale_train(IntPtr ann, IntPtr data);

        [DllImport("libfann.dll", EntryPoint = "fann_set_input_scaling_params")]
        static extern public
            int set_input_scaling_params(IntPtr ann, IntPtr data, float new_input_min, float new_input_max);

        [DllImport("libfann.dll", EntryPoint = "fann_set_output_scaling_params")]
        static extern public
            int set_output_scaling_params(IntPtr ann, IntPtr data, float new_output_min, float new_output_max);

        [DllImport("libfann.dll", EntryPoint = "fann_set_scaling_params")]
        static extern public
            int set_scaling_params(IntPtr ann, IntPtr data, float new_input_min,
            float new_input_max, float new_output_min, float new_output_max);

        [DllImport("libfann.dll", EntryPoint = "fann_clear_scaling_params")]
        static extern public
            int clear_scaling_params(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_scale_input")]
        static extern public
            void scale_input(IntPtr ann, float[] input_vector);

        [DllImport("libfann.dll", EntryPoint = "fann_scale_output")]
        static extern public
            void scale_output(IntPtr ann, float[] output_vector);

        [DllImport("libfann.dll", EntryPoint = "fann_descale_input")]
        static extern public
            void descale_input(IntPtr ann, float[] input_vector);

        [DllImport("libfann.dll", EntryPoint = "fann_descale_output")]
        static extern public
            void descale_output(IntPtr ann, float[] output_vector);

        [DllImport("libfann.dll", EntryPoint = "fann_scale_input_train_data")]
        static extern public
            void scale_input_train_data(IntPtr train_data, float new_min, float new_max);

        [DllImport("libfann.dll", EntryPoint = "fann_scale_output_train_data")]
        static extern public
            void scale_output_train_data(IntPtr train_data, float new_min, float new_max);

        [DllImport("libfann.dll", EntryPoint = "fann_scale_train_data")]
        static extern public
            void scale_train_data(IntPtr train_data, float new_min, float new_max);

        [DllImport("libfann.dll", EntryPoint = "fann_merge_train_data")]
        static extern public
            IntPtr merge_train_data(IntPtr data1, IntPtr data2);

        [DllImport("libfann.dll", EntryPoint = "fann_duplicate_train_data")]
        static extern public
            IntPtr duplicate_train_data(IntPtr data);

        [DllImport("libfann.dll", EntryPoint = "fann_subset_train_data")]
        static extern public
            IntPtr subset_train_data(IntPtr data, uint pos, uint length);

        [DllImport("libfann.dll", EntryPoint = "fann_length_train_data")]
        static extern public
            uint length(IntPtr data);

        [DllImport("libfann.dll", EntryPoint = "fann_num_input_train_data")]
        static extern public
            uint num_input(IntPtr data);

        [DllImport("libfann.dll", EntryPoint = "fann_num_output_train_data")]
        static extern public
            uint num_output(IntPtr data);

        [DllImport("libfann.dll", EntryPoint = "fann_save_train")]
        static extern public
            int save(IntPtr data, String filename);

        [DllImport("libfann.dll", EntryPoint = "fann_save_train_to_fixed")]
        static extern public
            int save_fixed(IntPtr data, String filename, uint decimal_point);

        [DllImport("libfann.dll", EntryPoint = "fann_get_training_algorithm")]
        static extern public
            train_algo get_training_algorithm(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_training_algorithm")]
        static extern public
            void set_training_algorithm(IntPtr ann, train_algo training_algorithm);

        [DllImport("libfann.dll", EntryPoint = "fann_get_learning_rate")]
        static extern public
            float get_learning_rate(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_learning_rate")]
        static extern public
            void set_learning_rate(IntPtr ann, float learning_rate);

        [DllImport("libfann.dll", EntryPoint = "fann_get_learning_momentum")]
        static extern public
            float get_learning_momentum(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_learning_momentum")]
        static extern public
            void set_learning_momentum(IntPtr ann, float learning_momentum);

        [DllImport("libfann.dll", EntryPoint = "fann_get_activation_function")]
        static extern public
            // ReSharper disable 
            Fann.activationFunc get_activation_function(IntPtr ann, int layer, int neuron);
        // ReSharper restore RedundantNameQualifier

        [DllImport("libfann.dll", EntryPoint = "fann_set_activation_function")]
        static extern public
            void set_activation_function(IntPtr ann, activationFunc activation_function, int layer, int neuron);

        [DllImport("libfann.dll", EntryPoint = "fann_set_activation_function_layer")]
        static extern public
            void set_activation_function_layer(IntPtr ann, activationFunc activation_function, int layer);

        [DllImport("libfann.dll", EntryPoint = "fann_set_activation_function_hidden")]
        static extern public
            void set_activation_function_hidden(IntPtr ann, activationFunc activation_function);

        [DllImport("libfann.dll", EntryPoint = "fann_set_activation_function_output")]
        static extern public
            void set_activation_function_output(IntPtr ann, activationFunc activation_function);

        [DllImport("libfann.dll", EntryPoint = "fann_get_activation_steepness")]
        static extern public
            float get_activation_steepness(IntPtr ann, int layer, int neuron);

        [DllImport("libfann.dll", EntryPoint = "fann_set_activation_steepness")]
        static extern public
            void set_activation_steepness(IntPtr ann, float steepness, int layer, int neuron);

        [DllImport("libfann.dll", EntryPoint = "fann_set_activation_steepness_layer")]
        static extern public
            void set_activation_steepness_layer(IntPtr ann, float steepness, int layer);

        [DllImport("libfann.dll", EntryPoint = "fann_set_activation_steepness_hidden")]
        static extern public
            void set_activation_steepness_hidden(IntPtr ann, float steepness);

        [DllImport("libfann.dll", EntryPoint = "fann_set_activation_steepness_output")]
        static extern public
            void set_activation_steepness_output(IntPtr ann, float steepness);

        [DllImport("libfann.dll", EntryPoint = "fann_get_train_error_function")]
        static extern public
            Fann.errorFunc get_error_function(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_train_error_function")]
        static extern public
            void set_error_function(IntPtr ann, Fann.errorFunc train_error_function);

        [DllImport("libfann.dll", EntryPoint = "fann_get_train_stop_function")]
        static extern public
            Fann.stopFunc get_stop_function(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_train_stop_function")]
        static extern public
            void set_train_stop_function(IntPtr ann, Fann.stopFunc train_stop_function);

        [DllImport("libfann.dll", EntryPoint = "fann_get_bit_fail_limit")]
        static extern public
            float get_bit_fail_limit(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_bit_fail_limit")]
        static extern public
            void set_bit_fail_limit(IntPtr ann, float bit_fail_limit);

        [DllImport("libfann.dll", EntryPoint = "fann_set_callback")]
        static extern public
            void set_callback(IntPtr ann, report_callback callback);

        [DllImport("libfann.dll", EntryPoint = "fann_get_quickprop_decay")]
        static extern public
            float get_quickprop_decay(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_quickprop_decay")]
        static extern public
            void set_quickprop_decay(IntPtr ann, float quickprop_decay);

        [DllImport("libfann.dll", EntryPoint = "fann_get_quickprop_mu")]
        static extern public
            float get_quickprop_mu(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_quickprop_mu")]
        static extern public
            void set_quickprop_mu(IntPtr ann, float quickprop_mu);

        [DllImport("libfann.dll", EntryPoint = "fann_get_rprop_increase_factor")]
        static extern public
            float get_rprop_increase_factor(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_rprop_increase_factor")]
        static extern public
            void set_rprop_increase_factor(IntPtr ann, float rprop_increase_factor);

        [DllImport("libfann.dll", EntryPoint = "fann_get_rprop_decrease_factor")]
        static extern public
            float get_rprop_decrease_factor(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_rprop_decrease_factor")]
        static extern public
            void set_rprop_decrease_factor(IntPtr ann, float rprop_decrease_factor);

        [DllImport("libfann.dll", EntryPoint = "fann_get_rprop_delta_min")]
        static extern public
            float get_rprop_delta_min(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_rprop_delta_min")]
        static extern public
            void set_rprop_delta_min(IntPtr ann, float rprop_delta_min);

        [DllImport("libfann.dll", EntryPoint = "fann_get_rprop_delta_max")]
        static extern public
            float get_rprop_delta_max(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_rprop_delta_max")]
        static extern public
            void set_rprop_delta_max(IntPtr ann, float rprop_delta_max);

        [DllImport("libfann.dll", EntryPoint = "fann_get_rprop_delta_zero")]
        static extern public
            float get_rprop_delta_zero(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_rprop_delta_zero")]
        static extern public
            void set_rprop_delta_zero(IntPtr ann, float rprop_delta_max);

    }
    public class IO
    {
        [DllImport("libfann.dll", EntryPoint = "fann_create_from_file")]
        static extern public
            IntPtr create_from_file(String configuration_file);

        [DllImport("libfann.dll", EntryPoint = "fann_save")]
        static extern public
            int save(IntPtr ann, String configuration_file);

        [DllImport("libfann.dll", EntryPoint = "fann_save_to_fixed")]
        static extern public
            int save_fixed(IntPtr ann, String configuration_file);


    }

    public class Cascade
    {
        [DllImport("libfann.dll", EntryPoint = "fann_cascadetrain_on_data")]
        static extern public
            void train_on_data(IntPtr ann, IntPtr data, uint max_neurons, uint neurons_between_reports, float desired_error);

        [DllImport("libfann.dll", EntryPoint = "fann_cascadetrain_on_file")]
        static extern public
            void train_on_file(IntPtr ann, String filename, uint max_neurons, uint neurons_between_reports, float desired_error);

        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_output_change_fraction")]
        static extern public
            float get_output_change_fraction(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_cascade_output_change_fraction")]
        static extern public
            void set_output_change_fraction(IntPtr ann, float cascade_output_change_fraction);

        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_output_stagnation_epochs")]
        static extern public
            uint get_output_stagnation_epochs(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_cascade_output_stagnation_epochs")]
        static extern public
            void set_output_stagnation_epochs(IntPtr ann, uint cascade_output_stagnation_epochs);

        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_candidate_change_fraction")]
        static extern public
            float get_candidate_change_fraction(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_cascade_candidate_change_fraction")]
        static extern public
            void set_candidate_change_fraction(IntPtr ann, float cascade_candidate_change_fraction);

        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_candidate_stagnation_epochs")]
        static extern public
            uint get_candidate_stagnation_epochs(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_cascade_candidate_stagnation_epochs")]
        static extern public
            void set_candidate_stagnation_epochs(IntPtr ann, uint cascade_candidate_stagnation_epochs);


        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_weight_multiplier")]
        static extern public
            float get_weight_multiplier(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_cascade_weight_multiplier")]
        static extern public
            void set_weight_multiplier(IntPtr ann, float cascade_weight_multiplier);

        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_candidate_limit")]
        static extern public
            float get_candidate_limit(IntPtr ann);


        [DllImport("libfann.dll", EntryPoint = "fann_set_cascade_candidate_limit")]
        static extern public
            void set_candidate_limit(IntPtr ann, float cascade_candidate_limit);


        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_max_out_epochs")]
        static extern public
            uint get_max_out_epochs(IntPtr ann);


        [DllImport("libfann.dll", EntryPoint = "fann_set_cascade_max_out_epochs")]
        static extern public
            void set_max_out_epochs(IntPtr ann, uint cascade_max_out_epochs);


        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_max_cand_epochs")]
        static extern public
            uint get_max_cand_epochs(IntPtr ann);


        [DllImport("libfann.dll", EntryPoint = "fann_set_cascade_max_cand_epochs")]
        static extern public
            void set_max_cand_epochs(IntPtr ann, uint cascade_max_cand_epochs);

        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_num_candidates")]
        static extern public
            uint get_num_candidates(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_activation_functions_count")]
        static extern public
            uint get_activation_functions_count(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_activation_functions")]
        static extern private
            IntPtr _get_activation_functions(IntPtr ann);

        public static activationFunc[] get_activation_functions(IntPtr ann)
        {
            uint funcs = get_activation_functions_count(ann);
            Fann.activationFunc[] afs = new activationFunc[funcs];
            int[] nums = new int[funcs];
            IntPtr ip = _get_activation_functions(ann);
            Marshal.Copy(ip, nums, 0, (int)funcs);
            for (int i = 0; i < funcs; ++i)
            {
                afs[i] = (Fann.activationFunc)nums[i];

            }
            return afs;

        }

        [DllImport("libfann.dll", EntryPoint = "fann_set_cascade_activation_functions")]
        static extern private
            void _set_activation_functions(IntPtr ann, activationFunc[] cascade_activation_functions, uint cascade_activation_functions_count);

        public static void set_activation_functions(IntPtr ann, activationFunc[] cascade_activation_functions)
        {
            _set_activation_functions(ann, cascade_activation_functions, (uint)cascade_activation_functions.Length);

        }


        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_activation_steepnesses_count")]
        static extern public
            uint get_activation_steepnesses_count(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_activation_steepnesses")]
        private static extern IntPtr _get_activation_steepnesses(IntPtr ann);

        public static float[] get_activation_steepnesses(IntPtr ann)
        {
            uint funcs = get_activation_steepnesses_count(ann);
            float[] steep = new float[funcs];
            IntPtr ip = _get_activation_steepnesses(ann);
            Marshal.Copy(ip, steep, 0, (int)funcs);

            return steep;

        }

        [DllImport("libfann.dll", EntryPoint = "fann_set_cascade_activation_steepnesses")]
        static extern private
            void _set_activation_steepnesses(IntPtr ann, float[] cascade_activation_steepnesses, uint cascade_activation_steepnesses_count);

        public static void set_activation_steepnesses(IntPtr ann, float[] cascade_activation_steepnesses)
        {
            _set_activation_steepnesses(ann, cascade_activation_steepnesses, (uint)cascade_activation_steepnesses.Length);

        }

        [DllImport("libfann.dll", EntryPoint = "fann_get_cascade_num_candidate_groups")]
        static extern public
            uint get_num_candidate_groups(IntPtr ann);

        [DllImport("libfann.dll", EntryPoint = "fann_set_cascade_num_candidate_groups")]
        static extern public
            void set_num_candidate_groups(IntPtr ann, uint cascade_num_candidate_groups);



    }
};